import fizzbuzz from "./fizzbuzz";

test("my test", () => {
  expect(fizzbuzz(1)).toBe("1");
  expect(fizzbuzz(3)).toBe("Fizz");
  expect(fizzbuzz(5)).toBe("Buzz");
  expect(fizzbuzz(15)).toBe("FizzBuzz");
});
