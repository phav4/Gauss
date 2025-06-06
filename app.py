# Simple Python program to take input and give output

def main():
    name = input("Enter your name: ")
    age = int(input("Enter your age: "))

    print(f"\nHello, {name}!")
    print(f"You are {age} years old.")
    print(f"In 5 years, you will be {age + 5} years old.")

if __name__ == "__main__":
    main()