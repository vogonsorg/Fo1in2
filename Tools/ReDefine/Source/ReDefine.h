#ifndef __REDEFINE__
#define __REDEFINE__    // :)

#include <map>
#include <regex>
#include <string>
#include <vector>

class Ini;

class ReDefine
{
public:

    //
    // ReDefine
    //

    Ini* Config;

    struct SStatus
    {
        struct SCurrent
        {
            std::string File;
            std::string Line;
            uint        LineNumber;

            SCurrent();
            void        Clear();
        }
        Current;

        void Clear();
    }
    Status;

    ReDefine();
    virtual ~ReDefine();

    void Init();
    void Finish();

    void DEBUG( const char* func, const char* format, ... );
    void WARNING( const char* func, const char* format, ... );
    void LOG( const char* format, ... );

    bool ReadFile( const std::string& path, std::vector<std::string>& lines );
    bool ReadConfig( const std::string& defines, const std::string& variable_prefix, const std::string& function_prefix );

    void ProcessHeaders( const std::string& path );
    void ProcessScripts( const std::string& path, bool readOnly = false );

    //
    // Defines
    //

    struct Header
    {
        const std::string Filename;
        const std::string Type;
        const std::string Prefix;
        const std::string Group;

        Header( const std::string& filename, const std::string& type, const std::string& prefix, const std::string& group );
    };

    std::vector<Header>                               Headers;
    std::map<std::string, std::map<int, std::string>> RegularDefines;
    std::map<std::string, std::vector<std::string>>   VirtualDefines;

    void FinishDefines();

    bool ReadConfigDefines( const std::string& section );
    bool ProcessHeader( const std::string& path, const Header& header );

    //
    // Operators
    //

    std::map<std::string, std::string> Operators;

    void InitOperators();
    void FinishOperators();

    bool        IsOperator( const std::string& opName );
    bool        IsOperatorName( const std::string& opName );
    std::string GetOperator( const std::string& opName );
    std::string GetOperatorName( const std::string& op );

    //
    // Text
    //

    bool        TextIsComment( const std::string& text );
    bool        TextGetInt( const std::string& text, int& result, const unsigned char& base = 10 );
    std::string TextGetTrimmed( const std::string& text );

    bool       TextIsDefine( const std::string& text );
    bool       TextGetDefine( const std::string& text, const std::regex& pattern, std::string& name, int& value );
    std::regex TextGetDefinePattern( const std::string& prefix, bool paren );

    //
    // Variables
    //

    std::map<std::string, std::string> Variables;

    void FinishVariables();

    bool ReadConfigVariables( const std::string& sectionPrefix );
};

#endif // __REDEFINE__ //
