#ifndef ICT_VALIDATE_H_
#define ICT_VALIDATE_H_
namespace ict{
    template<typename T>
    bool validate(const T& min, const T& max, const T* testValue, const int numElem, bool* res){
        bool result = false;
        int counter = 0;
        for(int i = 0; i < numElem; i++){
            if(testValue[i] >= min && testValue[i] <= max){
                result = true;
                res[i] = result;
                counter++;
            }else{
                result = false;
                res[i] = result;
            }
        }
        
        if(counter == numElem){
            return true;
        }else{
            return false;
        }


    };

}
#endif

