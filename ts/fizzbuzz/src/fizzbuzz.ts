export default function fizzbuzz(n: number) : string {
  let s = ""
  if (n % 3 === 0) {
    s = "Fizz";
  }
  if (n % 5 === 0) {
    s += "Buzz";
  }
  return s || `${n}`;
}
