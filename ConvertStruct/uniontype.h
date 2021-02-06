#ifndef UNIONTYPE_H
#define UNIONTYPE_H

#include <string>

template<typename T>
struct UnionType;

template<typename T>
struct UnionStandarType {
    union Size {
        T value_;
        char byteChar_[sizeof (T)];
    } type_;

    UnionStandarType() {}

    UnionStandarType( const T& value ) {
        this->type_.value_ = value;
    }

    UnionStandarType( T&& value ) {
        std::swap( this->type_.value_, value );
    }

    UnionStandarType &operator=( const T& value ) {
        this->type_.value_ = value;
        return *this;
    }

    UnionStandarType &operator=( T&& value ) {
        std::swap( this->type_.value_, value );
        return *this;
    }

    ~UnionStandarType() {}

    constexpr std::size_t sizeType() const {
        return sizeof (T);
    }

    T &value() {
        return this->type_.value_;
    }

    const T &value() const {
        return this->type_.value_;
    }

     char * byteChar() const {
        auto _arr = new char[sizeof (T)];
        std::char_traits<char>::copy( _arr, type_.byteChar_, sizeof (T) );
        return _arr;
    }

    void setByteChar( char *data ) {
        std::char_traits<char>::move( this->type_.byteChar_, data, sizeof (T) );
    }

};





template<> struct UnionType<bool> {
    UnionType() {}

    UnionType( bool value ) {
        this->type_ = value;
    }

    constexpr std::size_t sizeType() const {
        return 1;
    }

    bool &value() {
        return this->type_;
    }

    bool value() const {
        return this->type_;
    }

    char * yteChar() const {
        auto _arr = new char[1];
        _arr[0] = static_cast<char>( this->type_ );
        return _arr;
    }

    void setByteChar( char *data ) {
        this->type_ = static_cast<bool>( data[0] );
    }

    bool type_;
};





template<> struct UnionType<char> {
    UnionType() {}

    UnionType( char value ) {
        this->type_ = value;
    }

    constexpr std::size_t sizeType() const {
        return 1;
    }

    char &value() {
        return this->type_;
    }

    char value() const {
        return this->type_;
    }

    char * byteChar() const {
        auto _arr = new char[1];
        _arr[0] = this->type_;
        return _arr;
    }

    void setByteChar( char *data ) {
        this->type_ = data[0];
    }

    char type_;
};





template<> struct UnionType<short> final : UnionStandarType<short> {
    UnionType() : UnionStandarType() {}
    UnionType( short value ) : UnionStandarType<short>( value ) {}
    UnionType( short&& value ) : UnionStandarType<short>( std::move( value ) ) {}
    UnionType &operator=( short value ) {
        UnionStandarType<short>::operator=( value );
        return *this;
    }
    UnionType &operator=( short&& value ) {
        UnionStandarType<short>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<unsigned short> final : UnionStandarType<unsigned short> {
    UnionType() : UnionStandarType() {}
    UnionType( unsigned short value ) : UnionStandarType<unsigned short>( value ) {}
    UnionType( unsigned short&& value ) : UnionStandarType<unsigned short>( std::move( value ) ) {}
    UnionType &operator=( unsigned short value ) {
        UnionStandarType<unsigned short>::operator=( value );
        return *this;
    }
    UnionType &operator=( unsigned short&& value ) {
        UnionStandarType<unsigned short>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<int> final : UnionStandarType<int> {
    UnionType() : UnionStandarType() {}
    UnionType( int value ) : UnionStandarType<int>( value ) {}
    UnionType( int&& value ) : UnionStandarType<int>( std::move( value ) ) {}
    UnionType &operator=( int value ) {
        UnionStandarType<int>::operator=( value );
        return *this;
    }
    UnionType &operator=( int&& value ) {
        UnionStandarType<int>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<unsigned int> final : UnionStandarType<unsigned int> {
    UnionType() : UnionStandarType() {}
    UnionType( unsigned int value ) : UnionStandarType<unsigned int>( value ) {}
    UnionType( unsigned int&& value ) : UnionStandarType<unsigned int>( std::move( value ) ) {}
    UnionType &operator=( unsigned int value ) {
        UnionStandarType<unsigned int>::operator=( value );
        return *this;
    }
    UnionType &operator=( unsigned int&& value ) {
        UnionStandarType<unsigned int>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<long> final : UnionStandarType<long> {
    UnionType() : UnionStandarType() {}
    UnionType( long value ) : UnionStandarType<long>( value ) {}
    UnionType( long&& value ) : UnionStandarType<long>( std::move( value ) ) {}
    UnionType &operator=( long value ) {
        UnionStandarType<long>::operator=( value );
        return *this;
    }
    UnionType &operator=( long&& value ) {
        UnionStandarType<long>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<unsigned long> final : UnionStandarType<unsigned long> {
    UnionType() : UnionStandarType() {}
    UnionType( unsigned long value ) : UnionStandarType<unsigned long>( value ) {}
    UnionType( unsigned long&& value ) : UnionStandarType<unsigned long>( std::move( value ) ) {}
    UnionType &operator=( unsigned long value ) {
        UnionStandarType<unsigned long>::operator=( value );
        return *this;
    }
    UnionType &operator=( unsigned long&& value ) {
        UnionStandarType<unsigned long>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<long long> final : UnionStandarType<long long> {
    UnionType() : UnionStandarType() {}
    UnionType( long long value ) : UnionStandarType<long long>( value ) {}
    UnionType( long long&& value ) : UnionStandarType<long long>( std::move( value ) ) {}
    UnionType &operator=( long long value ) {
        UnionStandarType<long long>::operator=( value );
        return *this;
    }
    UnionType &operator=( long long&& value ) {
        UnionStandarType<long long>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<unsigned long long> final : UnionStandarType<unsigned long long> {
    UnionType() : UnionStandarType() {}
    UnionType( unsigned long long value ) : UnionStandarType<unsigned long long>( value ) {}
    UnionType( unsigned long long&& value ) : UnionStandarType<unsigned long long>( std::move( value ) ) {}
    UnionType &operator=( unsigned long long value ) {
        UnionStandarType<unsigned long long>::operator=( value );
        return *this;
    }
    UnionType &operator=( unsigned long long&& value ) {
        UnionStandarType<unsigned long long>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<float> final : UnionStandarType<float> {
    UnionType() : UnionStandarType() {}
    UnionType( float value ) : UnionStandarType<float>( value ) {}
    UnionType( float&& value ) : UnionStandarType<float>( std::move( value ) ) {}
    UnionType &operator=( float value ) {
        UnionStandarType<float>::operator=( value );
        return *this;
    }
    UnionType &operator=( float&& value ) {
        UnionStandarType<float>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<double> final : UnionStandarType<double> {
    UnionType() : UnionStandarType() {}
    UnionType( double value ) : UnionStandarType<double>( value ) {}
    UnionType( double&& value ) : UnionStandarType<double>( std::move( value ) ) {}
    UnionType &operator=( double value ) {
        UnionStandarType<double>::operator=( value );
        return *this;
    }
    UnionType &operator=( double&& value ) {
        UnionStandarType<double>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};

template<> struct UnionType<long double> final : UnionStandarType<long double> {
    UnionType() : UnionStandarType() {}
    UnionType( long double value ) : UnionStandarType<long double>( value ) {}
    UnionType( long double&& value ) : UnionStandarType<long double>( std::move( value ) ) {}
    UnionType &operator=( long double value ) {
        UnionStandarType<long double>::operator=( value );
        return *this;
    }
    UnionType &operator=( long double&& value ) {
        UnionStandarType<long double>::operator=( std::move( value ) );
        return *this;
    }
    ~UnionType() {}
};





template<> struct UnionType<std::string> {
    UnionType() {}

    UnionType( const std::string& value ) {
        this->type_ = value;
    }

    UnionType( std::string&& value ) {
        std::swap( this->type_, value );
    }

    UnionType &operator=( const std::string& value ) {
        this->type_ = value;
        return *this;
    }

    UnionType &operator=( std::string&& value ) {
        std::swap( this->type_, value );
        return *this;
    }

    ~UnionType() {}


    std::size_t sizeType() const {
        return this->type_.size() + 1;
    }

    std::string &value() {
        return this->type_;
    }

    const std::string &value() const {
        return this->type_;
    }

    const char * byteChar() const {
        auto _arr = new char[this->sizeType()];
        std::char_traits<char>::copy( _arr, this->type_.c_str(), this->sizeType() );
        return _arr;
    }

    void setByteChar( char *data ) {
        std::size_t _size = 0;
        for( std::size_t i = 0; ; i++ ) {
            if( data[i] == '\0' ) {
                _size = i + 1;
                break;
            }
        }
        auto _arr = new char[_size];
        std::char_traits<char>::move( _arr, data, _size );
        this->type_ = std::string( _arr );
        delete [] _arr;
    }

    std::string type_;
};


#endif // UNIONTYPE_H
