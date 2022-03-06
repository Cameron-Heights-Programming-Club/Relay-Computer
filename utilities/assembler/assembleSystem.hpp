#ifndef ASSEMBLE_SYSTEM_HPP
#define ASSEMBLE_SYSTEM_HPP

#include <vector>
#include <string>
#include <unordered_map>

enum class instrType {
    LABEL,
    LOAD,
    COMPUTE,
    JUMP
};

class assembleSystem {
public:
    assembleSystem(std::vector<std::string> asmInstructions, const std::string& outputFileName)
        : asmInstructions{ asmInstructions }, symbolTable {}, outputFileName{ outputFileName } {}
    int assemble();
private:
    void addNewLabel(const std::string& instr, size_t lineCount);
    void adjustLabelLoad(std::string& instr);
    instrType classifyInstruction(const std::string& instr);
    std::vector<std::string> asmInstructions;
    std::unordered_map<std::string, size_t> symbolTable;
    std::string outputFileName;
};

#endif // ASSEMBLE_SYSTEM_HPP