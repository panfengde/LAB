#ifndef LABTYPES
#define LABTYPES

namespace LabTypes
{
    enum LabTypes
    {
        undefined_type,
        number_type,
        string_type,
        boolean_type,
        class_type,
        function_type,
        list_type,
        cons_type,
        json_type,
        //下面的type，在LabEle中不会出现
        variable_type,
        keyword_type,
        frame_type,
    };

};

namespace keywordType
{
    enum keywordType
    {
        define,
        quote,
        set,
        get,
        _if,
        cons,
        array,
        json,
        begin,
        // let,
        lambda,
        _class,
        _new,
        define_syntax,
        sleep,
    };
};

enum codeType
{
    ele,
    exp
};

enum funType
{
    original,
    compound,
    macro,
};

enum frameType
{
    frame,
    topFrame
};

enum classFrameType
{
    topPototype,
    framePototype,
};

#endif