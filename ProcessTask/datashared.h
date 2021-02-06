#ifndef DATASHARED_H
#define DATASHARED_H

#include <memory>
#include <QString>
#include <QSharedMemory>

#include <QDebug>

template<typename T>
class DataShared
{
    DataShared( const DataShared &temp ) = delete;
    DataShared( DataShared &&temp ) = delete;

    DataShared &operator=( const DataShared &temp ) = delete;
    DataShared &operator=( DataShared &&temp ) = delete;
public:
    DataShared( const QString &nameSharedMemory, bool isNew = true );
    ~DataShared() = default;

    bool attashDs();
    bool detachDs();

    std::shared_ptr<T> readData();
    bool writeData( std::shared_ptr<T> data );

private:
    std::shared_ptr<QSharedMemory> data_;
};

template<typename T>
inline DataShared<T>::DataShared( const QString &nameSharedMemory, bool isNew )
{
    data_ = std::make_unique<QSharedMemory>( nameSharedMemory );
    if( isNew ) {
        data_->create( sizeof( T ) );
        T *_data = reinterpret_cast<T*>( data_->data() );
        T t;
        std::swap( t, *_data );
    }
}

template<typename T>
inline bool DataShared<T>::attashDs()
{
    return data_->attach();
}

template<typename T>
inline bool DataShared<T>::detachDs()
{
    return data_->detach();
}

template<typename T>
inline std::shared_ptr<T> DataShared<T>::readData()
{
    std::shared_ptr<T> _d;
    if( data_->lock() ) {
        T *_data = reinterpret_cast<T*>( data_->data() );
        if( _data == nullptr ){
            data_->unlock();
            return _d;
        }
        _d = std::make_shared<T>( *_data );
        data_->unlock();
        return _d;
    }
    return _d;
}
#include <iostream>
template<typename T>
bool DataShared<T>::writeData( std::shared_ptr<T> data )
{
    if( data_->lock() ) {
        T *_data = reinterpret_cast<T*>( data_->data() );
        if( _data == nullptr ){
            data_->unlock();
            return false;
        }
        _data->v1_ = data->v1_;
        _data->v2_ = data->v2_;
        _data->v3_ = data->v3_;
        data_->unlock();
        return true;
    }
    return false;
}

#endif // DATASHARED_H
