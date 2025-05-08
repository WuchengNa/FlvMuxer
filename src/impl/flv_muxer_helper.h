#pragma once

#include "common/common.h"
#include <vector>

class FLVMuxerHelper
{
private:
    /* data */
    FLVHeaderPtr flv_header_;
    
    std::vector<FLVTagPtr> flv_tags_list_;

public:
    FLVMuxerHelper();
    ~FLVMuxerHelper();
    
};