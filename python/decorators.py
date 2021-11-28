def dec1(dp1, dp2):
    def dec1_decorator(f):
        print("dec1_decorator")

        def f_wrapper(*args, **kwargs):
            print("f_wrapper")
            print(f">{dp1}-{dp2}")
            return f(*args, **kwargs)
        return f_wrapper
    return dec1_decorator


def dec2(dp1):
    def dec2_decorator(f):
        print("dec2_decorator")

        def f_wrapper(*args, **kwargs):
            print("f_wrapper")
            print(f">{dp1}")
            return f(*args, **kwargs)
        return f_wrapper
    return dec2_decorator


@dec1("abc", "def")
@dec2("ghi")
def my_function():
    print("xxx")


my_function()

# output:
# dec2_decorator
# dec1_decorator
# f_wrapper
# abc-def
# f_wrapper
# ghi
# xxx
