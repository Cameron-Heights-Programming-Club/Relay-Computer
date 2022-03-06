#include <iostream>
#include <fstream>

#include "assembleSystem.hpp"

int assembleSystem::assemble() {
    // Add ROM Labels
    size_t lineCount = 0;
    for (const std::string& instr : asmInstructions) {
        instrType type = classifyInstruction(instr);
        if (type == instrType::LABEL) {
            addNewLabel(instr, lineCount);
        } else {
            lineCount++;
        }
    }

    // ROM Jumps being converted
    for (std::string& instr : asmInstructions) {
        instrType type = classifyInstruction(instr);
        if (type == instrType::LOAD) {
            adjustLabelLoad(instr);
        }
    }

    std::ofstream machineCodeFile(outputFileName);

    // Convert all instructions
    for (const std::string& instr : asmInstructions) {
        instrType type = classifyInstruction(instr);
        switch (type) {
        case instrType::LOAD:
            break;
        case instrType::JUMP:
            break;
        case instrType::COMPUTE:
            break;
        default:
            std::cerr << "Missing implementation of instruction type\n";
            break;
        }
    }
}

void assembleSystem::adjustLabelLoad(std::string& instr) {
    const std::string labelName = instr.substr(1);

    bool onlyDigits = true;
    for (char c : instr) {
        onlyDigits = onlyDigits && std::isdigit(c);
    }

    if (onlyDigits) return;

    if (symbolTable.find(labelName) == symbolTable.end()) {
        std::cerr << "Label: " << labelName << "does not exist\n";
        return;
    }
    instr = "@" + std::to_string(symbolTable[labelName]);
}

void assembleSystem::addNewLabel(const std::string& instr, size_t lineCount) {
    const std::string labelName = instr.substr(1, instr.length() - 2);
    if (symbolTable.find(labelName) != symbolTable.end()) {
        std::cerr << "Duplicate label: " << labelName << '\n';
        return;
    }

    symbolTable[labelName] = lineCount;
}

instrType assembleSystem::classifyInstruction(const std::string& instr) {
    if (instr.starts_with("@")) {
        return instrType::LOAD;
    }

    if (instr.starts_with("(")) {
        return instrType::LABEL;
    }

    if (instr.find(';') != std::string::npos) {
        return instrType::JUMP;
    }

    return instrType::COMPUTE;
}