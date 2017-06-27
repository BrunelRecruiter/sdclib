# generateGSLfiles.py
# 
# created 22.06.17
# 
# autor: Sebastian Buerger @ surgiTAIX AG
# 
# This file is used to generate SimpleTypesMappings.h / ~.cpp, ConvertFromCDM.h / ~.cpp and ConvertToCDM.h / .cpp for the OSCLibrary
#
# to make changes in the generated files please edit the corresponding *_beginning, *_ending files


from lxml import etree
from io import StringIO, BytesIO

# typedefs
class CppTypdefStringBuilder(object):
    
    def __init__(self):
        ## init basetype_map for converting xsd-basetypes to cpp-basetypes
        # if a type is unknown the compiler throws a KeyError!
        self.basetype_map = {'xsd:unsignedLong' : 'unsigned long', 'pm:VersionCounter' : 'unsigned long', 'xsd:string' : 'std::string', 'xsd:decimal' : 'double', 'xsd:unsignedInt' : 'unsigned int'}
        self.content = ''
    
    def addTypedef(self, simpleType_name, baseTypeName_xsd):
        self.content = self.content + 'typedef ' + self.basetype_map[baseTypeName_xsd] + ' ' + simpleType_name + ';\n';
         
    def getCppTypedefString(self):
        return self.content + '\n\n'
        
# enums
class CppEnumClassBuilder(object):
    
    def __init__(self, simpleType_name):
        self.content = 'enum class' + simpleType_name + '\n{\n'
        
    def appendEnumEntry(self, enum_name):
        self.content = self.content + '\t' + enum_name + ',\n'
        
    def getEnumClassAsString(self):
        return self.content[:-2] + '\n};\n\n'
    
# EnumToStringClass declarations
class CppEnumToStringClassDeclarationBuilder(object):
    
    def __init__(self):
        self.content = 'class EnumToString {\npublic:\n'
        
    def addConvertFunctionDeclarationForSimpleType(self, simpleType_name):
        self.content = self.content + '\tstatic static std::string convert(' + simpleType_name + ' source);\n'
    
    def getEnumToStringClassDeclarationAsString(self):
        return self.content + '};\n\n';
    
# EnumToStringClass definition
class CppEnumToStringClassDefinitionBuilder(object):
    
    def __init__(self,simpleType_name):
        self.simpleType_name = simpleType_name
        self.content = 'std::string EnumToString::convert(' + self.simpleType_name + ' source) {\n\tswitch (source) {\n'
        
    def addConvertFunctionDefinitionForSimpleType(self,enum_name):
        self.content = self.content + '\t\tcase ' + self.simpleType_name + '::' + enum_name + ': return \"' + enum_name + '\"\n';
        
    def getEnumToStringClassDefinitionsAsString(self):
        return self.content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.simpleType_name + '\");\n}\n\n'

# ConvertFromCDM header
class CppConvertFromCDMClassDeclarationBuilder(object):
    def __init__(self):
        self.content = ''
        
    def addType(self, type_name):
        self.content = self.content + '\tstatic ' + type_name +' convert(const CDM::' + type_name + ' & source);\n'
        
    def getCoverterFunctionsDeclarationsAsString(self):
        return self.content


# Separate class for EnumConverterFunctions for ConvertFromCDM
# basetypes do not need any conversion
class CppConvertFromCDMClassEnumConverterFunctionBuilder(object):    
    def __init__(self, type_name):
        self.type_name = type_name
        self.content = self.type_name + ' ConvertFromCDM::convert(const CDM::' + self.type_name + ' & source) {\n\tswitch (source) {\n'
    
    def addConvertEnumEntry(self, enum_name):
        self.content = self.content + '\t\tcase CDM::' + self.type_name +  '::' + enum_name +': return ' + self.type_name + '::' + enum_name + ';\n'
        
    def getEnumConverterFunction(self):
        return self.content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.type_name + '\");\n}\n\n'
        

# ConvertFromCDM definition
class CppConvertFromCDMClassDefinitionBuilder(object):
    def __init__(self):
        self.enums = ''
        self.includes = ''
        self.complex = ''
    
    def addComplexType(self, type_name):
        self.complex = self.complex + type_name + 'ConvertFromCDM::convert(const CDM::' + type_name +' & source) {\n\treturn ' + type_name + '(source);\n}\n\n'
        self.includes = self.includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ include_name + '.h\"\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.enums = self.enums + enumConverterFunction_string;

    def getEnumsAsString(self):
        return self.enums;
    
    def getIncludesAsString(self):
        return self.includes
    
    def getComplexTypeFuctionsAsString(self):
        return self.complex
    
# ConvertToCDM header - simpleTypes only. complex types are transformed only in the definition via template method
class CppConvertToCDMClassDeclarationBuilder(object):
    def __init__(self):
        self.content = ''
        
    def addType(self, type_name):
        self.content = self.content + '\tstatic CDM::' + type_name +' convert(const ' + type_name + ' & source);\n'
        
    def getCoverterFunctionsDeclarationsAsString(self):
        return self.content

    
# Separate class for EnumConverterFunctions for ConvertToCDM
# basetypes do not need any conversion
class CppConvertToCDMClassEnumConverterFunctionBuilder(object):    
    def __init__(self, type_name):
        self.type_name = type_name
        self.content = 'CDM::' + self.type_name + ' ConvertToCDM::convert(const ' + self.type_name + ' & source) {\n\tswitch (source) {\n'
    
    def addConvertEnumEntry(self, enum_name):
        self.content = self.content + '\t\tcase ' + self.type_name +  '::' + enum_name +': return CDM::' + self.type_name + '::' + enum_name + ';\n'
        
    def getEnumConverterFunction(self):
        return self.content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.type_name + '\");\n}\n\n'
    

# ConvertToCDM definition
class CppConvertToCDMClassDefinitionBuilder(object):
    def __init__(self):
        self.enums = ''
        self.includes = ''
        self.complex = ''
    
    def addComplexType(self, type_name):
        self.complex = self.complex + 'template\nstd::unique_ptr<typename ' + type_name + 'WrappedType> ConvertToCDM::convert(const '+ type_name + '&source);'
        self.includes = self.includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ include_complexTypeName + '.h\"\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.enums = self.enums + enumConverterFunction_string;

    def getEnumsAsString(self):
        return self.enums;
    
    def getIncludesAsString(self):
        return self.includes


class GSLClassBuilder(object):    
    
    def __init__(self, class_name, parent_name, abstract_string):
        self.includes = ''
        self.properties = ''
        self.propertylists = ''
        self.typedefs = ''
        self.classdeclaration = '\t<class name = \"' + class_name + '\" parent = \"' + parent_name + '\" abstract = \"' + abstract_string + '\">\n'
        
    def addInclude(self,complexType_name):
        self.includes = self.includes + '\t\t<include path = \"OSCLib/Data/OSCP/MDIB/' + complexType_name + '.h\" />\n'
        
    def addProperty(self, property_name, property_type, optionality_bool):
        self.properties = self.properties + '\t\t<property name = \"' + property_name + '\" type = \"' + property_type + '\" optional = \"' + optionality_bool + '\" />\n'
    
    def addPropertyList(self, property_name, property_type):
        # automatically names nameServeral attaching a 's' to property_name
        self.propertylists = self.propertylists + '\t\t<propertyList nameSingle = \"' + property_name + '\" nameSeveral = \"' + property_name + 's\" type = \"' + property_type + '\" />\n'
        
    def addTypedef(self, typedef_name, typedef_type):
        self.typedefs = self.typedefs + '\t\t<typedef name = \"' + typedef_name + '\" type = \"' + typedef_type + '\" />\n'

    def getGSLClassAsString(self):
        return self.classdeclaration + self.includes + self.typedefs + self.properties + self.propertylists + '\t</class>\n\n' 

# contains the gsl descriptions
class GSLFileBuilder(object):
    def __init__(self):
        self.content = '<?xml version="1.0"?>\n<classes script = \"generate.gsl\" >'

    def addAbstractClassToSet(self, class_name):
        self.abstractClassesSet.add(class_name)

    def addClassAsString(self, class_string):
        self.content = self.content + class_string
        
    def getContent(self):
        return self.content + '</classes>'
    
# class: build files
class FileManager(object): 

    def writeToFile(self, filename, stringToWrite):
        with open(filename, 'w') as text_file:
            text_file.write(stringToWrite)
        
    def readFileToStr(self, filename):
        with open(filename, 'r') as myfile:
            data=myfile.read()
            return data




## factories
def make_FileManager():
    l_cppFileBuilder = FileManager()
    return l_cppFileBuilder

def make_CppEnumClassBuilder(simpleType_name):
    l_cppEnumClassBuilder = CppEnumClassBuilder(simpleType_name)
    return l_cppEnumClassBuilder

def make_CppEnumToStringClassBuilder():
    l_cppEnumToStringClassBuilder = CppEnumToStringClassDeclarationBuilder()
    return l_cppEnumToStringClassBuilder

def make_CppTypdefStringBuilder():
    l_cppTypdefStringBuilder = CppTypdefStringBuilder()
    return l_cppTypdefStringBuilder

def make_CppEnumToStringClassDefinitionBuilder(simpleType_name):
    l_cppEnumToStringClassDefinitionbuilder = CppEnumToStringClassDefinitionBuilder(simpleType_name)
    return l_cppEnumToStringClassDefinitionbuilder

def make_CppConvertFromCDMClassDeclarationBuilder():
    l_cppConvertFromCDMClassDeclarationBuilder = CppConvertFromCDMClassDeclarationBuilder()
    return l_cppConvertFromCDMClassDeclarationBuilder

def make_CppConvertFromCDMClassDefinitionBuilder():
    l_cppConvertFromCDMClassDefinitionBuilder = CppConvertFromCDMClassDefinitionBuilder()
    return l_cppConvertFromCDMClassDefinitionBuilder

def make_CppConvertFromCDMClassEnumConverterFunctionBuilder(simpleType_name):
    l_cppConvertFromCDMClassEnumConverterFunctionBuilder = CppConvertFromCDMClassEnumConverterFunctionBuilder(simpleType_name)
    return l_cppConvertFromCDMClassEnumConverterFunctionBuilder

def make_CppConvertToCDMClassDeclarationBuilder():
    l_cppConvertToCDMClassDeclarationBuilder = CppConvertToCDMClassDeclarationBuilder()
    return l_cppConvertToCDMClassDeclarationBuilder

def make_CppConvertToCDMClassEnumConverterFunctionBuilder(simpleType_name):
    l_cppConvertToCDMClassEnumConverterFunctionBuilder = CppConvertToCDMClassEnumConverterFunctionBuilder(simpleType_name)
    return l_cppConvertToCDMClassEnumConverterFunctionBuilder
    
def make_CppConvertToCDMClassDefinitionBuilder():
    l_cppConvertToCDMClassDefinitionBuilder = CppConvertToCDMClassDefinitionBuilder()
    return l_cppConvertToCDMClassDefinitionBuilder

def make_GSLFileBuilder():
    l_gslFileBuilder = GSLFileBuilder()
    return l_gslFileBuilder

def make_GSLClassBuilder(class_name, parent_name, abstract_bool):
    l_gslClassBuilder = GSLClassBuilder(class_name, parent_name, abstract_bool)
    return l_gslClassBuilder

## init
enumClasses_cppCode = ''
enumToStringClassMethods_cppCode = ''
cppTypdefStringBuilder = make_CppTypdefStringBuilder()
cppEnumToStringClassBuilder = make_CppEnumToStringClassBuilder()
cppConvertFromCDMClassDeclarationBuilder = make_CppConvertFromCDMClassDeclarationBuilder()
cppConvertFromCDMClassDefinitionBuilder = make_CppConvertFromCDMClassDefinitionBuilder()
cppConvertToCDMClassDeclarationBuilder = make_CppConvertToCDMClassDeclarationBuilder()
cppConvertToCDMClassDefinitionBuilder = make_CppConvertToCDMClassDefinitionBuilder()
gslFileBuilder = make_GSLFileBuilder()



###
### SimpleTypes
###
print '--- simple types ---'
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/BICEPS_MessageModel.xsd'),  etree.parse('../datamodel/ExtensionPoint.xsd') }:
    # search for simple type and go deeper
    # orientation: https://stackoverflow.com/questions/12657043/parse-xml-with-lxml-extract-element-value
    for simpleType_node in tree.xpath('//xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        enum_flag = False
        # only take nodes that have an attribute
        for attribute_name in simpleType_node.attrib:
            # get the name of the simple type
            simpleType_name = simpleType_node.attrib[attribute_name] # attribute_name = 'name'
            print simpleType_name
            
            # destinguish between enums and basetypes
            # enums
            for enum_node in simpleType_node.xpath('./xsd:restriction/xsd:enumeration', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                
                enum_entry = enum_node.attrib['value']
                print 'enum-type>>' + enum_entry
                # enum_Flag is False at the beginning of a new enum class -> reset classes
                if not enum_flag:
                    cppEnumClassBuilder = make_CppEnumClassBuilder(simpleType_name)
                    cppEnumToStringClassBuilder.addConvertFunctionDeclarationForSimpleType(simpleType_name)
                    cppEnumToStringClassDefinitionBuilder = make_CppEnumToStringClassDefinitionBuilder(simpleType_name)
                    cppConvertFromCDMClassEnumConverterFunctionBuilder = make_CppConvertFromCDMClassEnumConverterFunctionBuilder(simpleType_name)
                    cppConvertToCDMClassEnumConverterFunctionBuilder = make_CppConvertToCDMClassEnumConverterFunctionBuilder(simpleType_name)
                    
                # flag as enum
                enum_flag = True
                cppEnumClassBuilder.appendEnumEntry(enum_entry)
                cppEnumToStringClassDefinitionBuilder.addConvertFunctionDefinitionForSimpleType(enum_entry)
                cppConvertFromCDMClassEnumConverterFunctionBuilder.addConvertEnumEntry(enum_entry)
                cppConvertToCDMClassEnumConverterFunctionBuilder.addConvertEnumEntry(enum_entry)
                
                
            # basetypes
            if not enum_flag:
                for basetype_node in simpleType_node.xpath('./xsd:restriction', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    basetype_name = basetype_node.attrib['base']
                    print 'base-type>>' + basetype_name
                    cppTypdefStringBuilder.addTypedef(simpleType_name, basetype_name)
                
            # append code for each enum class
            if enum_flag:
                enumClasses_cppCode = enumClasses_cppCode + cppEnumClassBuilder.getEnumClassAsString()
                enumToStringClassMethods_cppCode = enumToStringClassMethods_cppCode + cppEnumToStringClassDefinitionBuilder.getEnumToStringClassDefinitionsAsString()
                cppConvertFromCDMClassDeclarationBuilder.addType(simpleType_name)
                cppConvertFromCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(cppConvertFromCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
                cppConvertToCDMClassDeclarationBuilder.addType(simpleType_name)
                cppConvertToCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(cppConvertToCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
                
            

###
### ComplexTypes
###

# # find abstract classes first
# print '--- abstract complexTypes ---'
# for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/BICEPS_MessageModel.xsd'),  etree.parse('../datamodel/ExtensionPoint.xsd') }:
#     # search for simple type and go deeper
#     # orientation: https://stackoverflow.com/questions/12657043/parse-xml-with-lxml-extract-element-value
#     for complexType_node in tree.xpath('//xsd:extension', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
#         # only take nodes that have an attribute
#         for attribute_name in complexType_node.attrib:
#             # get the name of the simple type
#             complexType_name = complexType_node.attrib[attribute_name] # attribute_name = 'base'

#             abstractClassName = complexType_name[(complexType_name.index(':')+1):]

#             gslFileBuilder.addAbstractClassToSet(abstractClassName)
#             print abstractClassName



# complexTypes
print '--- complexTypes ---'
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/BICEPS_MessageModel.xsd'),  etree.parse('../datamodel/ExtensionPoint.xsd') }:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # only take nodes that have an attribute
        for attribute_name in complexType_node.attrib:
            # get name
            complexType_name = complexType_node.attrib[attribute_name]
            # parent handling
            hasParents = False
            for complexTypeParent_node in complexType_node.xpath('./*/xsd:extension', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                hasParents = True
                for parentAttribute_name in complexTypeParent_node.attrib:
                    parentName_xsd = complexTypeParent_node.attrib[parentAttribute_name]
                    parentName = parentName_xsd[(parentName_xsd.index(':')+1):]
            
            if not hasParents:
                parentName = 'NULL'
                
            # consider only those types abstract that are named that way:
            abstractType_bool =  (complexType_name.find('Abstract') != -1)
            if abstractType_bool:
                abstract_string = 'true'
            else:
                abstract_string = 'false'
            
            glsClassBuilder = make_GSLClassBuilder(complexType_name, parentName, abstract_string)
            print complexType_name + ', parent= ' + parentName + ', abstract= ' + abstract_string

# for each class: add type
#cppConvertFromCDMClassDeclarationBuilder.addType(complexType_name) 




# build SimpleTypesMapping.h 
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.hxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.h', contentBeginning + cppTypdefStringBuilder.getCppTypedefString() + enumClasses_cppCode  + cppEnumToStringClassBuilder.getEnumToStringClassDeclarationAsString() + contentEnding)

#build SimpleTypesMapping.cpp 
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.cxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.cpp', contentBeginning + enumToStringClassMethods_cppCode + contentEnding)

#build ConvertFromCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertFromCDM.h', contentBeginning + cppConvertFromCDMClassDeclarationBuilder.getCoverterFunctionsDeclarationsAsString() + contentEnding)

#build ConvertFromCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertFromCDM.cpp', cppConvertFromCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertFromCDMClassDefinitionBuilder.getEnumsAsString() + contentEnding)

# build ConvertToCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertToCDM.h', contentBeginning + cppConvertToCDMClassDeclarationBuilder.getCoverterFunctionsDeclarationsAsString() + contentEnding)

#build ConvertToCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertToCDM.cpp', cppConvertToCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertToCDMClassDefinitionBuilder.getEnumsAsString() + contentEnding)


## complex types
#build complexTypesGSLformated.xml
cppFileBuilder = make_FileManager()
cppFileBuilder.writeToFile('complexTypesGSLformated.xml', 'asdf')




