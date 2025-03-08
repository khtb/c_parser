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
    Register(std::string name, std::string addressOffset, std::string size) : name(name), addressOffset(addressOffset), size(size) {};
    const std::string &getName() const { return name; };
    const std::string &getAddressOffset() const { return addressOffset; };
    const std::string &getSize() const { return size; };
    // const std::vector<Field> &getFields() const;
    // void addField(const Field &field);
private:
    std::string name;
    std::string addressOffset;
    std::string size;
    // std::vector<Field> fields;
};

#endif
