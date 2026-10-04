
#include "./lib/core.h"

// int heavyComputation(int x) {
//     // یک تسک کوچک‌تر که مربع x را محاسبه می‌کند
//     async t1([](int v) { return v * v; }, x);
//     int   sq = await(t1);  // بلاک می‌شویم تا t1 تمام شود

//     // یک تسک دیگر که به نتیجه‌ی اول عددی می‌افزاید
//     async t2([](int v) { return v + 42; }, sq);
//     int   res = await(t2);

//     return res;  // مجموع sq و 42
// }

int main() {
    // async t3(heavyComputation, 5);
    // let   hi = 5;
    // var   v1 = 10;

    // auto finalResult = await(t3);

    // std::cout << "Final result: " << finalResult << "\n";

    String name = "OpenAI";

    // Number pi = 3.1415;

    // List<Number> nums = {1.0, 2.0, 3.0};

    // Map<String, Number> scores;
    // scores[ "Alice" ] = 90;
    // scores[ "Bob" ]   = 85;

    // func<Number, Number, Number> add = [](Number a, Number b) { return a + b; };

    // Number sum = add(5.5, 4.5);

    // std::cout << "Name: " << name << "\n"
    //           << "Pi: " << pi << "\n"
    //           << "Sum: " << sum << "\n";

    // auto task = async([] { return 10; })
    //                 .then([](int x) {
    //                     std::cout << "Got: " << x << "\n";
    //                     return x * 2;
    //                 })
    //                 .then([](int y) { std::cout << "Doubled: " << y << "\n"; });

    // task.wait();

    // std::cout << "hi: " << *hi << "\n";
    // std::cout << "v1: " << v1 << "\n";

    return 0;
}

// int main() {
//     async task1([](int x) { return x * x; }, 5);

//     auto result1 = await(task1);
//     std::cout << "Result 1: " << result1 << "\n";

//     async task2([](int x) { return x + 10; }, 3);
//     auto result2 = await(task2);
//     std::cout << "Result 2: " << result2 << "\n";
// }
