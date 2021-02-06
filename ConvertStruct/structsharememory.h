#ifndef STRUCTSHAREMEMORY_H
#define STRUCTSHAREMEMORY_H

#include <tuple>
#include <memory>
#include "uniontype.h"
#include <iostream>
#include <vector>

template<class T, std::size_t N>
struct TupleSize {
    static std::size_t size( const T& t )
    {
        return std::get<N - 1>( t ).sizeType() + TupleSize<T, N - 1>::size( t );
    }
};

template<class T>
struct TupleSize<T, 1> {
    static std::size_t size( const T& t )
    {
        return std::get<0>( t ).sizeType();
    }
};

template<class T, std::size_t N>
struct TupleByteSize {
    static void byteSize( const T& t, char **start )
    {
        TupleByteSize<T, N - 1>::byteSize( t, start );
        decltype (auto) _item = std::get<N - 1>( t );
        auto _ptr = _item.byteChar();
        std::char_traits<char>::copy( *start, _ptr, _item.sizeType() );
        delete _ptr;
        *start += _item.sizeType();
    }
};

template<class T>
struct TupleByteSize<T, 1> {
    static void byteSize( const T& t, char **start )
    {
        decltype (auto) _item = std::get<0>( t );
        auto _ptr = _item.byteChar();
        std::char_traits<char>::copy( *start, _ptr, _item.sizeType() );
        delete _ptr;
        *start += _item.sizeType();
    }
};

template<class T, std::size_t N>
struct TupleData {
    static void byteData( const T& t, char **start )
    {
        TupleData<T, N - 1>::byteData( t, start );
        decltype (auto) _item = std::get<N - 1>( t );
        _item.setByteChar( *start );
        *start += _item.sizeType();
    }
};

template<class T>
struct TupleData<T, 1> {
    static void byteData( const T& t, char **start )
    {
        decltype (auto) _item = std::get<0>( t );
        _item.setByteChar( *start );
        *start += _item.sizeType();
    }
};

template<typename ...Arg>
class StructShareMemory : public std::tuple<UnionType<Arg>...>{
public:
    StructShareMemory() : std::tuple<UnionType<Arg>...>() {}

    StructShareMemory( const Arg& ... args ) : std::tuple<UnionType<Arg>...>( args... ) {}
    StructShareMemory( Arg&& ... args ) : std::tuple<UnionType<Arg>...>( args... ) {}

    std::tuple<UnionType<Arg>...> tuple() {
        return *this;
    }

    template<std::size_t N = 0>
    const auto &value() const {
        return std::get<N>( *this ).value();
    }

    std::size_t sizeType() const {
        return TupleSize<StructShareMemory, sizeof... (Arg)>::size( *this );
    }

    std::pair<const char *, size_t> dataByteChar() const {
        const auto _size = this->sizeType();
        auto _data = new char[_size];
        char *_start = _data;
        TupleByteSize<StructShareMemory, sizeof... (Arg)>::byteSize( *this, &_start );
        return std::make_pair( _data, _size );
    }

    void setByteChar( char *byteChar ) {
        TupleData<decltype (*this), sizeof... (Arg)>::byteData( *this, &byteChar );
    }
};




template<typename T>
struct IStruct {
    IStruct( const T *temp ) {
        this->temp_ = const_cast<T*>( temp );
    }

    std::pair<std::shared_ptr<const char[]>, size_t> byte( size_t size ) const {
        auto _data = this->temp_->structSharedMemory().dataByteChar();
        const auto _size = _data.second + sizeof(size_t);        
        auto _dataRes = new char[_size];
        char *_start = _dataRes;
        UnionType<size_t> _id( size );
        auto _dataId = _id.byteChar();
        std::char_traits<char>::move( _start, _dataId, sizeof(size_t) );
        delete[] _dataId;
        _start += sizeof(size_t);
        std::char_traits<char>::move( _start, _data.first, _data.second );
        delete [] _data.first;
        std::shared_ptr<const char[]> _ptr( _dataRes, []( auto a ) { delete[] a; } );
        return std::make_pair( _ptr, _size );
    }

    std::pair<const char*, size_t> byteChar() {
        return this->temp_->structSharedMemory().dataByteChar();
    }

    void setByteChar( char *byteChar ) {
        auto &&_ssm = std::move( this->temp_->structSharedMemory() );
        _ssm.setByteChar( byteChar );
        *this->temp_ = this->makeFromTuple( std::move( _ssm.tuple() ) );
    }

    template <typename Tuple, std::size_t... I>
    constexpr T makeFromTupleImpl( Tuple&& t, std::index_sequence<I...> )
    {
        return T{ std::get<I>( std::forward<Tuple>( t ) ).value()... };
    }

    template <typename Tuple>
    constexpr T makeFromTuple( Tuple&& t )
    {
        return this->makeFromTupleImpl( std::forward<Tuple>(t),
          std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{} );
    }

    T *temp_;
};


template<typename T>
struct UnionType{
    UnionType() {}

    UnionType( const T& value ) {
        this->type_ = value;
    }

    UnionType( T&& value ) {
        std::swap( this->type_, value );
    }

    UnionType &operator=( const T& value ) {
        this->type_ = value;
        return *this;
    }

    UnionType &operator=( T&& value ) {
        std::swap( this->type_, value );
        return *this;
    }

    ~UnionType() {}

    std::size_t sizeType() const {
        return this->type_.structSharedMemory().sizeType();
    }

    const T &value() {
        return this->type_;
    }

    const T &value() const {
        return this->type_;
    }

    const char *byteChar() const {
        return IStruct<T>( &this->type_ ).byteChar().first;
    }

    void setByteChar( char *data ) {
        IStruct<T>( &this->type_ ).setByteChar( data );
    }

    T type_;
};





template<typename T>
struct UnionType<std::vector<T>>{
    UnionType() {}

    UnionType( const std::vector<T>& value ) {
        this->type_ = value;
    }

    UnionType( std::vector<T>&& value ) {
        std::swap( this->type_, value );
    }

    UnionType &operator=( const std::vector<T>& value ) {
        this->type_ = value;
        return *this;
    }

    UnionType &operator=( std::vector<T>&& value ) {
        std::swap( this->type_, value );
        return *this;
    }

    ~UnionType() {}

    std::size_t sizeType() const {
        std::size_t _size = 0;
        for( const auto &i : this->type_ )
            _size += UnionType<T>( i ).sizeType();
        _size += ( this->type_.size() + 1 ) * sizeof ( std::size_t );
        return _size;
    }

    const std::vector<T> &value() {
        return this->type_;
    }

    const std::vector<T> &value() const {
        return this->type_;
    }

    const char *byteChar() const {
        std::size_t _uisize = this->type_.size();
        UnionType<std::size_t> _sizeVector( _uisize );
        const auto &_countVector = _sizeVector.sizeType();
        auto _arr = new char[this->sizeType()];
        auto _start = _arr;
        auto _byteCharSize = _sizeVector.byteChar();
        std::char_traits<char>::move( _start, _byteCharSize, _countVector );
        delete[] _byteCharSize;
        _start += _countVector;
        for( const auto &i : this->type_ ) {
            auto _item{ UnionType<T>( i ) };
            auto _sizeItem = _item.sizeType();
            UnionType<std::size_t> _sizeUtItem{ _sizeItem };
            auto _byteCharUnItem = _sizeUtItem.byteChar();
            std::char_traits<char>::move( _start, _byteCharUnItem, _sizeUtItem.sizeType() );
            delete [] _byteCharUnItem;
            _start += _sizeUtItem.sizeType();
            auto _byteChar = _item.byteChar();
            std::char_traits<char>::move( _start, _byteChar, _sizeItem );
            delete[] _byteChar;
            _start += _sizeItem;
        }
        return _arr;
    }

    void setByteChar( char *data ) {
        this->type_.clear();
        UnionType<std::size_t> _sizeVector;
        const auto &_size = _sizeVector.sizeType();
        auto _arr = new char[_size];
        std::char_traits<char>::move( _arr, data, _size );
        _sizeVector.setByteChar( _arr );
        delete[] _arr;
        data += _size;
        this->type_.reserve( _sizeVector.value() );
        for( std::size_t i = 0, size = _sizeVector.value(); i < size; i++ ) {
            UnionType<std::size_t> _sizeUtItem;
            auto _arr = new char[_sizeUtItem.sizeType()];
            std::char_traits<char>::move( _arr, data, _sizeUtItem.sizeType() );
            _sizeUtItem.setByteChar( _arr );
            delete[] _arr;
            data += _sizeUtItem.sizeType();

            UnionType<T> _item;
            _arr = new char[_sizeUtItem.value()];
            std::char_traits<char>::move( _arr, data, _sizeUtItem.value() );
            _item.setByteChar( _arr );
            delete[] _arr;
            data += _sizeUtItem.value();
            this->type_.push_back( std::move( _item.value() ) );
        }
    }

    std::vector<T> type_;
};

#endif // STRUCTSHAREMEMORY_H
