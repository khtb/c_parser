// mod2.cpp

#include <clang-c/Index.h>
#include <iostream>
#include <string>

void parseFile(const std::string& fileName) {
    // Initialize Clang index
    CXIndex index = clang_createIndex(0, 0);

    // Parse the file
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index, fileName.c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None);
    if (unit == nullptr) {
        std::cerr << "Unable to parse file: " << fileName << "\n";
        return;
    }

    // Visitor to print declarations
    auto visitor = [](CXCursor cursor, CXCursor parent, CXClientData data) {
        if (clang_getCursorKind(cursor) == CXCursor_FunctionDecl ||
            clang_getCursorKind(cursor) == CXCursor_ClassDecl) {
            CXString name = clang_getCursorSpelling(cursor);
            std::cout << "Found declaration: " << clang_getCString(name) << "\n";
            clang_disposeString(name);
        }
        return CXChildVisit_Recurse;
    };

    // Visit the top-level declarations in the translation unit
    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(cursor, visitor, nullptr);

    // Clean up
    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}
