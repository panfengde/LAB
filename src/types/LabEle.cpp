//
// Created by 潘峰 on 2022/7/1.
//
#include "LabEle.h"

//LabEle *LabEle::get(LabEle *attr) {
//    attr->show();
//    //std::cout << "init---addName2-----------" << std::endl;
//    //base_prototype->look_vars_frame(addName2).show();
//    return property->look_variable_env(attr);
//};

LabEle *LabEle::get(LabEle *key) {
    auto result = LabEleTool::createLabEle();
    switch (this->type) {
        case LabTypes::number_type:
            return (this->numberV()->get(key));
            break;
        case LabTypes::string_type:
            return (this->stringV()->get(key));
            break;
        case LabTypes::boolean_type:
            return (this->booleanV()->get(key));
            break;
        case LabTypes::insertType:
            return (this->insertTypeV()->get(key));
            break;
        case LabTypes::class_type:
            return (this->listV()->get(key));
            break;
        case LabTypes::function_type:
            return (this->listV()->get(key));
            break;
        case LabTypes::list_type:
            return (this->listV()->get(key));
            break;
        case LabTypes::keyword_type:
            return (this->listV()->get(key));
            break;
        case LabTypes::variable_type:
            return (this->listV()->get(key));
            break;
        case LabTypes::undefined_type:
            return result;
            break;
        case LabTypes::frame_type:
            return (this->frameV()->look_variable_prototype(key));
            break;
        case LabTypes::cons_type:
            return this->consV()->get(key);
            break;
        case LabTypes::json_type:
            return this->jsonV()->get(key);
            break;
        default:
            return result;
            break;
    };
}

LabEle::LabEle() {
};

Lab_undefined *LabEle::undefinedV() {
    return reinterpret_cast<Lab_undefined *>(this);
}

Lab_number *LabEle::numberV() {
    return reinterpret_cast<Lab_number *>(this);
}


Lab_boolean *LabEle::booleanV() {
    return reinterpret_cast<Lab_boolean *>(this);
}

Lab_insertType *LabEle::insertTypeV() {
    return reinterpret_cast<Lab_insertType *>(this);
}

Lab_string *LabEle::stringV() {
    return reinterpret_cast<Lab_string *>(this);
}

Lab_cons *LabEle::consV() {
    return reinterpret_cast<Lab_cons *>(this);
}


Lab_list *LabEle::listV() {
    return reinterpret_cast<Lab_list *>(this);
}

Lab_json *LabEle::jsonV() {
    return reinterpret_cast<Lab_json *>(this);
}


Lab_variable *LabEle::variableV() {
    return reinterpret_cast<Lab_variable *>(this);
}

Lab_class *LabEle::classV() {
    return reinterpret_cast<Lab_class *>(this);
}

Lab_function *LabEle::functionV() {
    return reinterpret_cast<Lab_function *>(this);
}

Lab_keyWord *LabEle::keyWordV() {
    return reinterpret_cast<Lab_keyWord *>(this);
}

Frame *LabEle::frameV() {
    return reinterpret_cast<Frame *>(this);
}

LabEle *LabEle::set(LabEle *obj) {
    switch (obj->type) {
        case LabTypes::number_type: {
            type = LabTypes::number_type;
            *(numberV()) = *(obj->numberV());
            return this;
        }
        case LabTypes::string_type: {
            type = LabTypes::string_type;
            *(stringV()) = *(obj->stringV());
            return this;
        }
        case LabTypes::boolean_type:
            type = LabTypes::boolean_type;
            *(booleanV()) = *(obj->booleanV());
            return this;
        case LabTypes::class_type: {
            type = LabTypes::class_type;
            *(classV()) = *(obj->classV());
            return this;
        }
        case LabTypes::function_type: {
            type = LabTypes::function_type;
            *(functionV()) = *(obj->functionV());
            return this;
        }
        case LabTypes::list_type: {
            type = LabTypes::list_type;
            *(listV()) = *(obj->listV());
            return this;
        }
        case LabTypes::keyword_type: {
            throw "can't set var keyWord";
            return this;
        }
        case LabTypes::variable_type: {
            type = LabTypes::variable_type;
            *(variableV()) = *(obj->variableV());
            return this;
        }
        case LabTypes::undefined_type: {
            type = LabTypes::undefined_type;
            *(undefinedV()) = *(obj->undefinedV());
            return this;
        }
        case LabTypes::frame_type: {
            type = LabTypes::frame_type;
            *(frameV()) = *(obj->frameV());
            return this;
        }
        case LabTypes::cons_type: {
            type = LabTypes::cons_type;
            *(consV()) = *(obj->consV());
            return this;
        }
        case LabTypes::json_type: {
            type = LabTypes::frame_type;
            *(jsonV()) = *(obj->jsonV());
            return this;
        }
        default: {
            return this;
        }
    }
};

string LabEle::stringify() {
    return value;
}
