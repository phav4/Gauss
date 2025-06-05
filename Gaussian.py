def gauss_jordan(augmented, n):
    for i in range(n):
        # Find the row with the maximum value in the current column
        max_row = max(range(i, n), key=lambda r: abs(augmented[r][i]))
        if abs(augmented[max_row][i]) < 1e-12:
            raise ValueError("Matrix is singular or nearly singular.")

        # Swap current row with the row with the max pivot
        if max_row != i:
            augmented[i], augmented[max_row] = augmented[max_row], augmented[i]

        # Normalize pivot row
        pivot = augmented[i][i]
        augmented[i] = [x / pivot for x in augmented[i]]

        # Eliminate other rows
        for k in range(n):
            if k != i:
                factor = augmented[k][i]
                augmented[k] = [a - factor * b for a, b in zip(augmented[k], augmented[i])]
    return augmented

def main():
    try:
        n = int(input("Enter the size of the matrix (n): "))
        if n <= 0:
            raise ValueError("Matrix size must be positive.")

        print(f"\nEnter the {n}x{n} matrix A row by row (each row has {n} values):")
        A = []
        for i in range(n):
            row = list(map(float, input(f"Row {i+1} of A: ").split()))
            while len(row) != n:
                print(f"Each row must have {n} values.")
                row = list(map(float, input(f"Row {i+1} of A: ").split()))
            A.append(row)

        print(f"\nEnter the RHS vector b (must have {n} values):")
        b = list(map(float, input("b: ").split()))
        while len(b) != n:
            print(f"RHS vector must have {n} values.")
            b = list(map(float, input("b: ").split()))

        # Build augmented matrix: [A | I | b]
        augmented = []
        for i in range(n):
            identity = [1.0 if i == j else 0.0 for j in range(n)]
            augmented.append(A[i] + identity + [b[i]])

        # Perform Gauss-Jordan Elimination with pivoting
        augmented = gauss_jordan(augmented, n)

        # Output solution vector x
        print("\nSolution Vector x:")
        for i in range(n):
            print(f"x{i+1} = {augmented[i][-1]:.6f}")

        # Output inverse of A
        print("\nInverse of A:")
        for i in range(n):
            print(" ".join(f"{augmented[i][n + j]:.6f}" for j in range(n)))

    except ValueError as e:
        print("Input Error:", e)

if __name__ == "__main__":
    main()
