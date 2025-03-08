#ifndef SVD_PARSER_H
#define SVD_PARSER_H

#include <string>
#include <vector>
#include <tinyxml2.h>

class Peripheral;
class Register;
class Field;

class SVDParser
{
public:
    SVDParser(std::string svdFileName) : svdFileName(svdFileName) {}
    const std::vector<Peripheral> &getPeripherals() const  { return peripherals; };
    bool parse();

private:
    std::string svdFileName;
    std::vector<Peripheral> peripherals;
    bool parsePeripheral(tinyxml2::XMLElement *element);
    bool parseRegister(tinyxml2::XMLElement *element, Peripheral &peripheral);
    bool parseField(tinyxml2::XMLElement* element ,Register &reister);
};

class Peripheral
{
public:
    Peripheral(std::string name, uint32_t baseAddress) : name(name), baseAddress(baseAddress),registers({}) {};
    Peripheral(std::string name, uint32_t baseAddress,std::vector<Register> registers) : name(name), baseAddress(baseAddress),registers(registers) {};
    const std::string &getName() const { return name; };
    const std::uint32_t &getBaseAddress() const { return baseAddress; };
    const std::vector<Register> &getRegisters() const { return registers; };
    void addRegister(const Register &reg);
    
    private:
    std::string name;
    std::uint32_t baseAddress;
    std::vector<Register> registers;
};


class Register
{
public:
    Register(std::string name, std::string addressOffset, std::string size) : name(name), addressOffset(addressOffset), size(size), fields({})  {};
    Register(std::string name, std::string addressOffset, std::string size , std::vector<Field> fields) : name(name), addressOffset(addressOffset), size(size), fields(fields)  {};

    const std::string &getName() const { return name; };
    const std::string &getAddressOffset() const { return addressOffset; };
    const std::string &getSize() const { return size; };
    const std::vector<Field> &getFields() const { return fields; };
    void addField(const Field &field);
private:
    std::string name;
    std::string addressOffset;
    std::string size;
    std::vector<Field> fields;
};


class Field
{
public:
    Field(std::string name, std::string bitOffset, std::string bitWidth) : name(name), bitOffset(bitOffset), bitWidth(bitWidth) {};
    const std::string &getName() const { return name; };
    const std::string &getBitOffset() const { return bitOffset; };
    const std::string &getBitWidth() const { return bitWidth; };
private:
    std::string name;
    std::string bitOffset;
    std::string bitWidth;
};


#endif
