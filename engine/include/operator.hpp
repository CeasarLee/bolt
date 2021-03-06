// Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#ifndef _OPERATOR_H
#define _OPERATOR_H

#include <string>
#include "sys.h"
#include "tensor_computing.h"
#include "tensor.hpp"
#include "model_tools.h"

#include <map>
#define HashMap std::map

template<Arch A > class Operator {
public:
    virtual bool check() { return true; }; //only for debug
    virtual void run() = 0;

    /**
     * @param inputTensors
     * @param outputTensors
     */
    virtual void set_input_output_tensors(Vec<Tensor> it, Vec<Tensor> ot)
    {
        this->inputTensors = it;
        this->outputTensors = ot;
    }

    virtual Vec<Tensor> get_input_tensors()
    {
        return this->inputTensors;
    }

    virtual Vec<Tensor> get_output_tensors()
    {
        return this->outputTensors;
    }

    virtual void set_input_tensors(Vec<Tensor> it)
    {
        this->inputTensors = it;
    }

    virtual void set_output_tensors(Vec<Tensor> ot)
    {
        this->outputTensors = ot;
    }

    virtual bool can_input_output_the_same() { return false; }

    virtual EE infer_output_tensors_size(Vec<TensorDesc>, Vec<TensorDesc>*) = 0;

    std::string get_name()
    {
       return this->name;
    }
    /**
     * @param name
     */
    explicit Operator(std::string name)
    {
        this->name = name;
    }

    Operator():name("") { }

    virtual bool is_weight()
    {
        return false;
    }

    virtual U32 infer_tmp_memory_size()
    {
        this->lenOfTemp = 0;
        this->temp = std::shared_ptr<U8>();
        return 0;
    }


    virtual void set_tmp_memory(U32 len, std::shared_ptr<U8> temp)
    {
        this->lenOfTemp = len;
        this->temp = temp;
    }

    virtual U32 get_len_of_temp()
    {
        return this->lenOfTemp;
    }

    virtual std::shared_ptr<U8> get_tmp()
    {
        return this->temp;
    }

    virtual void set_op_type(OperatorType opType)
    {
        this->opType = opType;
    }

    virtual OperatorType get_op_type()
    {
        return this->opType;
    }

    virtual void set_op_name(std::string opName) {
        this->name = opName;
    }

    virtual ~Operator(){ }

public:
    DataType dt;

    Vec<Tensor> inputTensors;
    Vec<Tensor> outputTensors;

    U32 lenOfTemp;
    std::shared_ptr<U8> temp;

    std::string name;

    OperatorType opType;
};

#endif //_OPERATOR_H
