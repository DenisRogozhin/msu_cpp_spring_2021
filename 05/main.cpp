#include "serializer.h"


struct Data {
    	uint64_t a;
        bool b;
    	uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a, &b, &c);
    }
};

struct Data1 {
    	bool a;
        bool b;
    	uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a, &b, &c);
    }
};

struct Data2 {
    	char a;
        bool b;
    	uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a, &b, &c);
    }
};


struct Data3 {
    	uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&c);
    }
};


void ok_test() {
    Data x { 3333, true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    assert(x.a == 3333);
    assert(x.b == true);
    assert(x.c == 2);
}

void CorruptedArchive_test() {
    Data x { 3, true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    Data1 y { false, true, 2 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::CorruptedArchive);
    assert(false == y.a);
    assert(true == y.b);
    assert(2 == y.c);
}

void WrongType_test() {
    Data2 x { 'a', true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    Data2 y { 'b', true, 2 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::WrongType); 
    assert(err2 == Error::WrongType);
}

void small_data_test() {
    Data3 x { 124324};
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    Data3 y { 45344 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::NoError);
    assert(x.c == y.c);
    assert(x.c == 124324);
}

int main() {
    ok_test();
    CorruptedArchive_test();
    WrongType_test();
    small_data_test();
    return 0;
}





