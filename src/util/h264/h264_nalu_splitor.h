#pragma once 
#include <stdint.h>
#include <vector>
#include <memory>

class H264NALU
{
public:
    uint8_t nalu_type_; // 5 bits
    uint8_t nalu_ref_idc_; // 2 bits
    uint8_t forbidden_zero_bit_; // 1 bit
    uint8_t* data_;
    size_t   data_size_;
public:
    H264NALU(){}
    ~H264NALU(){}
};


class H264NALUSplitor
{  
public:
    H264NALUSplitor(uint8_t* data, size_t size)
    :data_(data)
    ,size_(size)
    ,cur_(data)
    {}
    
    ~H264NALUSplitor()
    {

    }

    bool Split(){
        if (data_ == nullptr || size_ == 0) {
            return false;
        }
        
        size_t offset = 0;

        do{
            offset = seekNaluBegin(&cur_, size_);
            if(offset != -1 ){
                if(nalu_list_.size() > 0){
                    nalu_list_.back().data_size_ = nalu_list_.back().data_size_ - offset;
                }
                H264NALU nalu;
                nalu.forbidden_zero_bit_ = (data_[offset] & 0x80) >> 7;
                nalu.nalu_ref_idc_ = (data_[offset] & 0x60) >> 5;
                nalu.nalu_type_ = (data_[offset] & 0x1F);
                nalu.data_ = const_cast<uint8_t*>(data_ + offset);
                nalu.data_size_ = size_ - offset;
                nalu_list_.push_back(nalu);
            }
        }while(offset != -1);     

        if(nalu_list_.empty()){
            return false;
        }   
        return true;
    }
    
    std::vector<H264NALU> GetNALUs() const { return nalu_list_; }
    void Clear() {
        nalu_list_.clear();
    }

private:
    uint8_t seekNaluBegin(uint8_t** cur, size_t size){
        uint8_t* data = *cur;
        for(size_t i = 0; i < size - 3; ++i) {
            if(data[i] != 0x01){
                continue;
            }
            //check privious three bytes
            if (data[i - 1] == 0x00 && data[i - 2] == 0x00 && data[i - 3] == 0x00) {
                cur += 4;
                return i+3;
            }

            //check privious two bytes
            if (data[i - 1] == 0x00 && data[i - 2] == 0x00) {
                cur += 3;
                return i+2;
            }

        }
        return -1;
    }
    uint8_t* cur_;
    uint8_t* data_;
    size_t size_;
    std::vector<H264NALU> nalu_list_;
};