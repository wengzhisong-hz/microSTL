#ifndef MICROSTL_ALGOBASE_H
#define MICROSTL_ALGOBASE_H

namespace MicroSTL {
    template<typename OutputIterator, typename Size, typename T>
    OutputIterator fill_n(OutputIterator first, Size n, const T &value) {
        for (; n > 0; --n, ++first) {
            *first = value;
        }
        return first;
    }
}

#endif //MICROSTL_ALGOBASE_H
