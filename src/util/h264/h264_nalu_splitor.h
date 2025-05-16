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
    ,end_(data + size)
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
            offset = seekNaluHead(data_,end_,&cur_);
            if (offset == -1)
                break;

            if (!nalu_list_.empty())
                nalu_list_.back().data_size_ = (data_ + offset) - nalu_list_.back().data_;
           
            H264NALU nalu;
            nalu.data_ = cur_;
            nalu.data_size_ = end_ - cur_ ;
            nalu.forbidden_zero_bit_ = cur_[0] & (0x01<<7);// 1bit
            nalu.nalu_ref_idc_ = cur_[0] & (0x03<<5); //2bit
            nalu.nalu_type_ = cur_[0]& 0x1F ; //5bit
            nalu_list_.push_back(nalu);
        }while(offset != -1);
        return true;
    }
    
    std::vector<H264NALU> GetNALUs() const { return nalu_list_; }
    void Clear() {
        nalu_list_.clear();
    }

private:
    size_t seekNaluHead(const uint8_t* begin, const uint8_t* end, uint8_t** cur ){
        uint8_t* data = *cur;
        for(; data < end; ++data){
            //check 0x00 0x00 0x00 0x01 or 0x00 0x00 0x01            
            if(*data != 0x01){
                continue;
            }
            //check privious three bytes
            if (data - 3 >= *cur
                && *(data - 3) == 0x00 && *(data - 2) == 0x00 && *(data - 1) == 0x00) {
                auto ret = data - 3 - begin;
                *cur = data+1;
                return ret;
            }
            //check privious two bytes
            if (data - 2 >= *cur
                && *(data - 2) == 0x00 && *(data - 1) == 0x00) {
                auto ret = data -2 - begin;
                *cur = data+1;
                return ret;
            }
        }
        return -1;
    }


    uint8_t* cur_;
    uint8_t* end_;
    uint8_t* data_;
    size_t size_;
    std::vector<H264NALU> nalu_list_;
};