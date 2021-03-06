// Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include "tensor_computing.h"
#include "utils.h"

int main(int argc, char** argv) {
    CHECK_REQUIREMENT(argc == 4);
    U32 len = atoi(argv[1]);
    F16 alpha = (F16)atof(argv[2]);
    F16 beta  = (F16)atof(argv[3]);

    DataType dt = DT_F16;
    TensorDesc input_desc = tensor1d(dt, len); 
    TensorDesc output_desc;
    CHECK_STATUS(multiply_infer_output_size(input_desc, &output_desc));

    F16* input = ut_input_v<F16>(len, UT_INIT_RANDOM);
    F16* output = ut_input_v<F16>(len, UT_INIT_ZERO);
    F16* output_ref = ut_input_v<F16>(len, UT_INIT_ZERO);

    if (UT_CHECK) {
        CHECK_STATUS(multiply(&alpha, &beta, input_desc, input, output_desc, output, UT_ARCH));

        // naive implement
        CHECK_STATUS(multiply(&alpha, &beta, input_desc, input, output_desc, output_ref, CPU_GENERAL));

        // check
        ut_check_v<F16>(output, output_ref, len, F16(0), __FILE__, __LINE__);
    }

    // benchmark
    double time_start = ut_time_ms();
    for (int iter = 0; iter < UT_LOOPS; iter ++) {
        CHECK_STATUS(multiply(&alpha, &beta, input_desc, input, output_desc, output, UT_ARCH));
    }
    double time_end = ut_time_ms();
    double time = (time_end - time_start) / UT_LOOPS;

    // log performance data
    char buffer[150];
    char params[120];
    sprintf(params, "(%u)=(%u)",
                    len, len);
    sprintf(buffer, "%20s, %80s", "Multiply", params);
    double ops = 2.0 * len;
    ut_log<F16>(buffer, ops, time/UT_LOOPS);

    free(input);
    free(output);
    free(output_ref);

    return 0;
}
