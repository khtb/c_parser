#include "svdParser.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <string>


bool SVDParser::parse()
{
    tinyxml2::XMLDocument doc;
    if(doc.LoadFile(svdFileName.c_str()) != tinyxml2::XML_SUCCESS)
    {
        spdlog::error("Failed to load SVD file");
        return false;
    }

    tinyxml2::XMLElement *root = doc.RootElement();
    if(!root)
    {
        spdlog::error("Failed to get root element");
        return false;
    }
    
    tinyxml2::XMLElement *device = root->FirstChildElement("peripherals");
    if (device)
    {
        tinyxml2::XMLElement *peripheral = device->FirstChildElement("peripheral");
        while(peripheral)
        {
            if(!parsePeripheral(peripheral))
            {
                spdlog::error("Failed to parse peripheral");
                return false;
            }
            peripheral = peripheral->NextSiblingElement("peripheral");
        }
    }
    else
    {
        spdlog::error("Failed to get device element");
        return false;
    }
    return true;

}


bool SVDParser::parsePeripheral(tinyxml2::XMLElement *element)
{
    const char * name_pu8 = element->FirstChildElement("name")->GetText();
    const char * baseAddress_pu8 = ""; 
    uint32_t baseAddress;
    baseAddress_pu8= element->FirstChildElement("baseAddress")->GetText();
    std::string nameStr(name_pu8);
    baseAddress = std::stoul(baseAddress_pu8, nullptr, 16);
    Peripheral peripheral(nameStr, baseAddress);
    tinyxml2::XMLElement *regsElement = element->FirstChildElement("registers");
    if(regsElement)
    {
        tinyxml2::XMLElement *reg = regsElement;//->FirstChildElement("register");
        while(reg)
        {
            if(!parseRegister(reg, peripheral))
            {
                spdlog::error("Failed to parse register");
                return false;
            }
            reg = reg->NextSiblingElement("register");
        }
    }
    else
    {
        spdlog::error("Failed to get register element");
        return false;
    }
    peripherals.push_back(peripheral);
    return true;
}



bool SVDParser::parseRegister(tinyxml2::XMLElement *element, Peripheral &peripheral)
{
    for (tinyxml2::XMLElement *reg = element->FirstChildElement("register"); reg != nullptr; reg = reg->NextSiblingElement("register"))
    {
        std::string name_str = reg->FirstChildElement("name")->GetText();
        std::string addressOffset_str = reg->FirstChildElement("addressOffset")->GetText();
        std::string size_str = reg->FirstChildElement("size")->GetText();
        uint32_t addressOffset = std::stoul(addressOffset_str, nullptr, 16); // Convert hex string to uint32_t
        Register regElem(name_str, addressOffset_str,size_str);
        // fields
        tinyxml2::XMLElement *field = reg->FirstChildElement("field");
        while(field)
        {
            parseField(field, regElem);
            field = field->NextSiblingElement("field");
            peripheral.addRegister(regElem);
        }
    }
    return true;
}

bool SVDParser::parseField(tinyxml2::XMLElement* element ,Register &reg)
{
    while (element)
    {
        std::string name_str = element->FirstChildElement("name")->GetText();
        std::string bitOffset_str = element->FirstChildElement("bitOffset")->GetText();
        std::string bitWidth_str = element->FirstChildElement("bitWidth")->GetText();
        Field fieldElem(name_str, bitOffset_str, bitWidth_str);
        reg.addField(fieldElem);
        element = element->NextSiblingElement("field");
    }
    return true;
}


void Peripheral::addRegister(const Register &reg)
{
    registers.push_back(reg);
}

void Register::addField(const Field &field)
{
    fields.push_back(field);
}




void parseTest(void)
{
    SVDParser parser("large_dummy_svd_file.svd");	
	parser.parse();
	std::vector<Peripheral> peripherals = parser.getPeripherals();
	for (Peripheral peripheral : peripherals)
	{
		spdlog::info("Peripheral name: {}", peripheral.getName());
		spdlog::info("Peripheral base address: {:#x}", peripheral.getBaseAddress());
		for ( const Register &reg : peripheral.getRegisters())
		  {
			spdlog::info("    Register name: {}", reg.getName());
			spdlog::info("    Register address offset: {}", reg.getAddressOffset());
			spdlog::info("    Register size: {}", reg.getSize());
			for (const Field &field : reg.getFields())
			{
				spdlog::info("        Field name: {}", field.getName());
				spdlog::info("        Field bit offset: {}", field.getBitOffset());
				spdlog::info("        Field bit width: {}", field.getBitWidth());
			}
		}
	}
}