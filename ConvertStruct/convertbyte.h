#ifndef CONVERTBYTE_H
#define CONVERTBYTE_H

#include "structsharememory.h"

template<typename T> size_t idStruct() {
    return 0;
}

template<typename T>
class ConverByte final {
public:
    ConverByte() {
        this->value_ = std::make_shared<T>();
    }

    ConverByte( T temp ) {
        this->value_ = std::make_shared<T>( temp );
    }

    void setData( T temp ) {
        this->value_ = std::make_shared<T>( temp );
    }

    std::shared_ptr<T> data() const {
        return this->value_;
    }

    std::pair<std::shared_ptr<const char[]>, size_t> bytes() const {
        size_t _id = idStruct<T>();
        IStruct<T> _struct( this->value_.get() );
        return _struct.byte( _id );
    }

    std::shared_ptr<T> convertBytes( const char * data ) {
        return this->convertBytes( const_cast<char*>( data ) );
    }

    bool isConvertBytes( const char * data ) const {
        return this->isConvertBytes( const_cast<char*>( data ) );
    }

    size_t id( const char * data ) const {
        return this->dataIdStruct( const_cast<char*>( data ) );
    }

private:
    std::shared_ptr<T> value_;

    std::shared_ptr<T> convertBytes( char * data ) {
        this->value_.reset();
        char *_start = data;
        UnionType<size_t> _id;
        _id.setByteChar( _start );
        _start += sizeof(size_t);
        if( idStruct<T>() == _id.value() ) {
            this->value_ = std::make_shared<T>();
            IStruct<T> _cs( this->value_.get() );
            _cs.setByteChar( _start );
        }
        return this->value_;
    }

    bool isConvertBytes( char * data ) const {
        UnionType<size_t> _id;
        _id.setByteChar( data );
        return ( idStruct<T>() == _id.value() );
    }

    size_t id( char * data ) const {
        UnionType<size_t> _id;
        _id.setByteChar( data );
        return _id.value();
    }

};

#endif // CONVERTBYTE_H
