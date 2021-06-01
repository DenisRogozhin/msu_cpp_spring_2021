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


struct Data4 {
    	uint64_t a;
        bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a, &b);
    }
};


struct Data5 {
    	bool c;

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


void only_bool_test() {
    Data5 x { true};
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(stream.str() == "true");
    assert(err1 == Error::NoError);
    Data5 y { false };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::NoError);
    assert(x.c == y.c);
    assert(x.c == true);

}

void less_data_test() {
    Data x { 3333, true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 == Error::NoError);
    assert(stream.str() == "3333 true 2");
    Data4 y { 0, false};
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::NoError);
    assert(x.a == 3333);
    assert(x.b == true);
    assert(x.c == 2);
    assert(y.a == 3333);
    assert(y.b == true);
}


void more_data_test() {
    Data4 y { 0, false};
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(y);
    assert(err1 == Error::NoError);
    assert(stream.str() == "0 false");
    Data x { 3333, true, 2 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(x);
    assert(err2 == Error::NotEnoughData);
    assert(x.a == 0);
    assert(x.b == false);
    assert(x.c == 2);
    assert(y.a == 0);
    assert(y.b == false);
}


void ok_test() {
    Data x { 3333, true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(stream.str() == "3333 true 2");
    assert(err1 == Error::NoError);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
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
    assert(stream.str() == "3 true 2");
    assert(err1 == Error::NoError);
    Data1 y { false, true, 2 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::CorruptedArchive);
    assert(false == y.a);
    assert(true == y.b);
    assert(2 == y.c);
    assert(x.a == 3);
    assert(x.b == true);
    assert(x.c == 2);
}

void WrongType_test() {
    Data2 x { 'a', true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 == Error::WrongType); 
    Data2 y { 'b', true, 2 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::NotEnoughData);
    assert('b' == y.a);
    assert(true == y.b);
    assert(2 == y.c);
    assert(x.a == 'a');
    assert(x.b == true);
    assert(x.c == 2);
}

void small_data_test() {
    Data3 x { 124324};
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 == Error::NoError);
    assert(stream.str() == "124324");
    Data3 y { 45344 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::NoError);
    assert(x.c == y.c);
    assert(x.c == 124324);
}

void bad_int_test() {
    std::stringstream stream;
    stream<<"1243243453453454342342432432394854395893458349583495834593478999999999999999999999999999999999999999995934573495347542343242342342";
    Data3 y { 45344 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::Bad_uint64);
    assert(45344 == y.c);
}


struct Data6 {
    std::string c;


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

void other_data_test() {
    Data x { 0, true, 1 };
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(stream.str() == "0 true 1");
    assert(err1 == Error::NoError);
    Data y { 2, false, 3 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    assert(x.a == 0);
    assert(x.b == true);
    assert(x.c == 1);
}   



void strange_string() {
    Data6 x { "word"};
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 == Error::WrongType);
    stream<<"word";
    Data3 y { 45344 };
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::Bad_uint64);
    assert(x.c == "word");
    assert(y.c == 45344);

} 


int main() {
    bad_int_test();
    more_data_test();
    less_data_test();
    ok_test();
    CorruptedArchive_test();
    WrongType_test();
    small_data_test();
    only_bool_test();
    strange_string();
    other_data_test();
    return 0;
}





