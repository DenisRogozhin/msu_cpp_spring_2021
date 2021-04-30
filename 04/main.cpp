#include "BigInt.h"

void operator_plus_test() {
    BigInt a1("5");
    BigInt a2("1000000000000");
    BigInt a3("1234567890");
    BigInt a4("9999999999");
    assert(a3 + a4 == BigInt("11234567889"));
    assert(a1 + a2 == BigInt("1000000000005"));
    BigInt a5("-5");
    assert(a5 + a2 == BigInt("999999999995"));
    assert(a2 + a5 == BigInt("999999999995"));
    BigInt a6("-1000000000000");
    assert(a5 + a6 == BigInt("-1000000000005"));
    assert(a6 + 1 == BigInt("-999999999999"));
    assert(a2 + 13 == BigInt("1000000000013"));
}

void operator_minus_test() {
    BigInt a1("-5");
    BigInt a2("1000000000000");
    BigInt a3("1234567890");
    BigInt a4("9999999999");
    assert(a4 - a3 == BigInt("8765432109"));
    assert(a3 - a4 == BigInt("-8765432109"));
    assert(a1 - a2 == BigInt("-1000000000005"));
    BigInt a5("5");
    BigInt a6("-1000000000000");
    assert(a2 - a5 == BigInt("999999999995"));
    assert(a5 - a6 == BigInt("1000000000005"));
    assert(a2 - 5 == BigInt("999999999995"));
}

void operator_mul_test() {
    BigInt a1("-5");
    BigInt a2("1000000000000");
    BigInt a3("1234567890");
    BigInt a4("9999999999");
    assert(a4 * a3 == BigInt("12345678898765432110"));
    assert(a1 * a2 == BigInt("-5000000000000"));
    BigInt a5("5");
    BigInt a6("-1000000000000");
    assert(a2 * a5 == BigInt("5000000000000"));
    assert(a1 *  a6 == BigInt("5000000000000"));
    assert(a2 * 5 == BigInt("5000000000000"));
}

void operator_eq_and_not_eq_test() {
    BigInt a1("-5");
    BigInt a2("5");
    BigInt a3("-5");
    BigInt a4("99324932492");
    BigInt a5("99324932492");
    BigInt a6("-99324932492");
    BigInt a7("99324932491");
    BigInt a8("99324932490");
    assert(!(a1 == a2) && (a1 == a3) && (a4 == a5) && !(a4 == a6) && !(a4 == a7) && !(a4 == a8) && !(a2 == a5));
    assert((a1 != a2) && !(a1 != a3) && !(a4 != a5) && (a4 != a6) && (a4 != a7) && (a4 != a8) && (a2 != a5));
}

void compare_operators_test() {
    BigInt a1("-5");
    BigInt a2("5");
    BigInt a3("-5");
    BigInt a4("99324932492");
    BigInt a5("99324932492");
    BigInt a6("-99324932492");
    BigInt a7("99324932491");
    BigInt a8("99324932493");

    assert(!(a1 > a2) && (a2 > a1) && !(a3 > a1) && !(a4 > a5) && (a4 > a7) && !(a4 > a8) && !(a2 > a5) && (a1 > a6));
    assert(!(a1 >= a2) && (a2 >= a1) && (a3 >= a1) && (a4 >= a5) && (a4 >= a7) && !(a4 >= a8) && !(a2 >= a5) && (a1 >= a6));

    assert((a1 < a2) && !(a2 < a1) && !(a3 < a1) && !(a4 < a5) && !(a4 < a7) && (a4 < a8) && (a2 < a5) && !(a1 < a6));
    assert((a1 <= a2) && !(a2 <= a1) && (a3 <= a1) && (a4 <= a5) && !(a4 <= a7) && (a4 <= a8) && (a2 <= a5) && !(a1 <= a6));
}

void operator_un_minus_test() {
    BigInt a1("-5");
    BigInt a2("5");
    assert(a1 == -a2);
    assert(a2 == -a1);
}

void operator_print_test() {
    BigInt a1("00002354234234324234238476237474234243543563442134");
    BigInt a2("-00000000000000000000000000000003242342345553454");
    std::cout<<a1<<std::endl;
    std::cout<<a2<<std::endl;
}


void useless_zeroes_test() {
    BigInt a1("000000000999999999");
    BigInt a2("000001");
    assert(a1 + a2 == BigInt("1000000000"));
}

void move_and_copy_test() {
    BigInt a1("349593459345934953495934953294");
    BigInt a2(a1);
    assert(a2 == a1);
    BigInt a3;
    a3 = a1;
    assert(a3 == a1);
    BigInt a4(std::move(a1));
    assert(a4 == a2);
    BigInt a5; 
    a5 = std::move(a2);
    assert(a5 == a3);

}

int main() {
    operator_plus_test();
    operator_minus_test();
    operator_mul_test();
    operator_eq_and_not_eq_test();
    compare_operators_test();
    operator_print_test();
    operator_un_minus_test();
    useless_zeroes_test();
    move_and_copy_test();

}





