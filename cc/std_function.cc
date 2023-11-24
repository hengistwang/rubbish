#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

int add_one(int input) { return input + 1; }

bool validate_vector_add_one(std::vector<int> const &input_vector,
                             std::vector<int> const &output_vector) {
  bool is_valid{true};
  for (size_t i{0}; i < input_vector.size(); ++i) {
    if (output_vector.at(i) != input_vector.at(i) + 1) {
      is_valid = false;
      break;
    }
  }
  return is_valid;
}

void reset_vector(std::vector<int> &input_vector) {
  for (size_t i{0}; i < input_vector.size(); ++i) {
    input_vector.at(i) = 0;
  }
}

template <typename T, typename Func>
void unitary_function_pass_by_lambda_function(T &output, T const &input,
                                              Func const func) {
  output = func(input);
}

template <typename T>
void unitary_function_pass_by_std_function_value(
    T &output, T const &input, std::function<T(T)> const func) {
  output = func(input);
}

template <typename T>
void unitary_function_pass_by_std_function_reference(
    T &output, T const &input, std::function<T(T)> const &func) {
  output = func(input);
}

template <typename T>
void unitary_function_pass_by_function_pointer(T &output, T const &input,
                                               T (*func)(T)) {
  output = func(input);
}

int main() {
  // Set floating point format std::cout with 3 decimal places.
  std::cout.precision(3);

  size_t const num_elements{10000000};
  std::vector<int> input_vector(num_elements, 0);
  std::vector<int> output_vector(num_elements, 0);

  auto const lambda_function_add_one{
      [](int const &input) -> int { return input + 1; }};
  std::function<int(int)> const std_function_add_one{lambda_function_add_one};

  std::cout << "The size of a function pointer: " << sizeof(&add_one)
            << std::endl;
  std::cout << "The size of a std::function pointer: "
            << sizeof(&std_function_add_one) << std::endl;
  std::cout << "The size of a std::function: " << sizeof(std_function_add_one)
            << std::endl;

  // Call function frequently in a vanilla way.
  // The compiler knows what function to call at compile time and can optimize
  // the code.
  // This is the best performance we could get.
  std::chrono::steady_clock::time_point const time_start_vanilla{
      std::chrono::steady_clock::now()};
  for (size_t i{0}; i < num_elements; ++i) {
    output_vector.at(i) = add_one(input_vector.at(i));
  }
  std::chrono::steady_clock::time_point const time_end_vanilla{
      std::chrono::steady_clock::now()};
  auto const time_elapsed_vanilla{
      std::chrono::duration_cast<std::chrono::nanoseconds>(time_end_vanilla -
                                                           time_start_vanilla)
          .count()};
  float const latency_vanilla{time_elapsed_vanilla /
                              static_cast<float>(num_elements)};
  std::cout << "Latency Pass Vanilla: " << latency_vanilla << " ns"
            << std::endl;
  assert(validate_vector_add_one(input_vector, output_vector));
  reset_vector(output_vector);

  // Sometimes, we don't know what function to call at compile time.
  // We can use std::function to pass a function as an argument.
  // In this case, we pass the std::function by value.
  // Because the size of a std::function is 32 bytes, passing by value
  // results in a lot of copying and bad performance.
  std::chrono::steady_clock::time_point const
      time_start_pass_by_std_function_value{std::chrono::steady_clock::now()};
  for (size_t i{0}; i < num_elements; ++i) {
    unitary_function_pass_by_std_function_value(
        output_vector.at(i), input_vector.at(i), std_function_add_one);
  }
  std::chrono::steady_clock::time_point const
      time_end_pass_by_std_function_value{std::chrono::steady_clock::now()};
  auto const time_elapsed_pass_by_std_function_value{
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          time_end_pass_by_std_function_value -
          time_start_pass_by_std_function_value)
          .count()};
  float const latency_pass_by_std_function_value{
      time_elapsed_pass_by_std_function_value /
      static_cast<float>(num_elements)};
  std::cout << "Latency Pass By Std Function Value: "
            << latency_pass_by_std_function_value << " ns" << std::endl;
  assert(validate_vector_add_one(input_vector, output_vector));
  reset_vector(output_vector);

  // Instead of passing the std::function by value, we can pass it by
  // reference (pointer). In this case, object copying is eliminated. The
  // performance is better than passing the std::function by value. However,
  // the performance is still not as good as the vanilla way.
  std::chrono::steady_clock::time_point const
      time_start_pass_by_std_function_reference{
          std::chrono::steady_clock::now()};
  for (size_t i{0}; i < num_elements; ++i) {
    unitary_function_pass_by_std_function_reference(
        output_vector.at(i), input_vector.at(i), std_function_add_one);
  }
  std::chrono::steady_clock::time_point const
      time_end_pass_by_std_function_reference{std::chrono::steady_clock::now()};
  auto const time_elapsed_pass_by_std_function_reference{
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          time_end_pass_by_std_function_reference -
          time_start_pass_by_std_function_reference)
          .count()};
  float const latency_pass_by_std_function_reference{
      time_elapsed_pass_by_std_function_reference /
      static_cast<float>(num_elements)};
  std::cout << "Latency Pass By Std Function Reference: "
            << latency_pass_by_std_function_reference << " ns" << std::endl;
  assert(validate_vector_add_one(input_vector, output_vector));
  reset_vector(output_vector);

  // std::function is a general purpose wrapper for function pointers,
  // callable objects, and lambda functions. Because it's general purpose,
  // it's not as efficient as a function pointer. In this case, we pass a
  // function pointer to a function. The performance is better than passing
  // the std::function by reference.
  std::chrono::steady_clock::time_point const
      time_start_pass_by_function_pointer{std::chrono::steady_clock::now()};
  for (size_t i{0}; i < num_elements; ++i) {
    unitary_function_pass_by_function_pointer(output_vector.at(i),
                                              input_vector.at(i), &add_one);
  }
  std::chrono::steady_clock::time_point const time_end_pass_by_function_pointer{
      std::chrono::steady_clock::now()};
  auto const time_elapsed_pass_by_function_pointer{
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          time_end_pass_by_function_pointer -
          time_start_pass_by_function_pointer)
          .count()};
  float const latency_pass_by_function_pointer{
      time_elapsed_pass_by_function_pointer / static_cast<float>(num_elements)};
  std::cout << "Latency Pass By Function Pointer: "
            << latency_pass_by_function_pointer << " ns" << std::endl;
  assert(validate_vector_add_one(input_vector, output_vector));
  reset_vector(output_vector);

  // We can also pass a lambda function to a function.
  // The compiler knows what function to call at compile time and can optimize
  // the code. The performance is also better than passing the std::function
  // by reference.
  std::chrono::steady_clock::time_point const
      time_start_pass_by_lambda_function{std::chrono::steady_clock::now()};
  for (size_t i{0}; i < num_elements; ++i) {
    unitary_function_pass_by_lambda_function(
        output_vector.at(i), input_vector.at(i), lambda_function_add_one);
  }
  std::chrono::steady_clock::time_point const time_end_pass_by_lambda_function{
      std::chrono::steady_clock::now()};
  auto const time_elapsed_pass_by_lambda_function{
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          time_end_pass_by_lambda_function - time_start_pass_by_lambda_function)
          .count()};
  float const latency_pass_by_lambda_function{
      time_elapsed_pass_by_lambda_function / static_cast<float>(num_elements)};
  std::cout << "Latency Pass By Lambda Function: "
            << latency_pass_by_lambda_function << " ns" << std::endl;
  assert(validate_vector_add_one(input_vector, output_vector));
  reset_vector(output_vector);
}
