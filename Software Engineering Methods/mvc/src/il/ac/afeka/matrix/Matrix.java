package il.ac.afeka.matrix;

import java.util.Arrays;
import java.util.Random;

public class Matrix {

	private Double[][] m;
	private int nRows, nCols;
	
	public Matrix(int nRows, int nCols) {
		this.nRows = nRows;
		this.nCols = nCols;
		
		m = new Double[nRows][nCols];
	}
	
	public static Matrix zero(int nRows, int nCols) {

		Matrix zero = new Matrix(nRows, nCols);

		for(int i =0; i < nRows; i++) 
			for(int j = 0; j < nCols; j++)
				zero.m[i][j] = 0.0;

		return zero;	
	}
	
	public static Matrix Identity(int n) {

		return fromScalar(n, 1.0);
	}
	
	public static Matrix random(int nRows, int nCols) {
		
		Random r = new Random();
		
		Matrix result = new Matrix(nRows, nCols);
		for(int i = 0; i < nRows; i++)
			for(int j = 0; j < nCols ; j++)
				result.m[i][j] = r.nextDouble();
		
		return result;
	}
	
	public static Matrix fromScalar(int n, Double d) {
		
		Matrix identity = zero(n,n);
		
		for(int i = 0; i < n; i++)
			identity.m[i][i] = d;	
		
		return identity;
	}
	
	public Matrix(Matrix other) {
		for(int i =0; i < 3; i++)
			for(int j =0;j < 3;j++)
				this.m[i][j] = other.m[i][j];
	}
	
	public void putAt(int row, int col, Double value) {
		m[row][col] = value;
	}
	
	public Double at(int row, int col) {
		return m[row][col];
	}
	
	public Matrix multBy(Matrix other) {
		
		assert other.nRows == this.nCols;
		
		Matrix result = new Matrix(this.nRows, other.nCols);

		for(int i = 0; i < this.nRows; i ++)
			for (int j = 0; j < other.nCols; j++) {
				result.m[i][j] = 0.0;
				for(int k = 0; k < this.nCols; k++)
					result.m[i][j] = result.m[i][j] + this.m[i][k]*other.m[k][j];
			}
		
		return result;
	}
	
	public int getNrows() {
		return nRows;
	}

	public int getNcols() {
		return nCols;
	}

	public Matrix addTo(Matrix other) {
		
		assert sameDimensionAs(other);
		
		Matrix result = new Matrix(nRows, nCols);
		
		for(int i = 0; i < nRows; i ++)
			for (int j = 0; j < nCols; j++) {
					result.m[i][j] = this.m[i][j] + other.m[i][j];
			}
		
		return result;
	}
	
	public boolean sameDimensionAs(Matrix other) {
		return nRows == other.nRows && nCols == other.nCols;
	}

	public Matrix multBy(double scalar) {

		Matrix result = new Matrix(nRows, nCols);
		
		for(int i = 0; i < nRows; i++)
			for(int j = 0; j < nCols; j++)
				result.m[i][j] = m[i][j] * scalar;
		
		return result;
	}
	
	public Matrix transpose() {
		
		Matrix result = new Matrix(nCols, nRows);
		
		for(int i = 0 ; i < nRows; i++)
			for(int j = 0; j < nCols; j++)
				result.m[j][i] = this.m[i][j];
						
		return result;
	}
	
	public Matrix minor(int row, int col) {
	
		assert nRows > 0;
		assert nCols > 0;
		
		Matrix result = new Matrix(nRows - 1, nCols - 1);
		
		for(int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				result.m[i][j] = this.m[i][j];
			for (int j = col + 1; j < nCols; j++)
				result.m[i][j-1] = this.m[i][j];
		}
		
		for(int i = row+1; i < nRows; i++) {
			for (int j = 0; j < col; j++)
				result.m[i-1][j] = this.m[i][j];
			for (int j = col + 1; j < nCols; j++)
				result.m[i-1][j-1] = this.m[i][j];
		}
			
		return result;
	}
	
	public Double determinant() {
		
		assert nCols == nRows;
		
		if (nCols == 1)
			return m[0][0];
		
		Double result = 0.0;
		
		for(int i = 0; i < nRows; i++) 
			result = result + (i % 2 == 0 ? 1 : -1) * m[i][0] * minor(i,0).determinant();
		
		return result;
	}
	
	public Matrix adjoint() {
		
		assert nRows == nCols;
		
		Matrix result = new Matrix(nRows, nCols);
		
		for(int i = 0; i < nRows; i++)
			for (int j = 0; j < nCols; j++)
				result.m[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor(i,j).determinant();
		
		return result.transpose();
	}
	
	public Matrix invert() {
		return adjoint().multBy(1/determinant());
	}

	@Override
	public int hashCode() {	
		return 31 + Arrays.deepHashCode(m);
	}

	@Override
	public boolean equals(Object other) {
		
		return getClass() == other.getClass() && Arrays.deepEquals(m, ((Matrix)other).m);
	}
	
	public boolean equalsWithTolerance(Matrix other, Double tolerance) {
		
		if (nRows != other.nRows || nCols != other.nCols)
			return false;
		
		for(int i = 0; i < nRows; i++)
			for (int j = 0; j < nCols; j++)
				if (Math.abs(this.m[i][j] - other.m[i][j]) > tolerance)
					return false;

		return true;
	}

	@Override
	public String toString() {
		String result = "";
		
		result += "[";
		for (int i = 0; i < nRows; i++) {
			result += "[";
			if (nCols > 0)
				result += m[i][0].toString();
			for (int j = 1; j < nCols; j++) {
				result += "," + m[i][j].toString();
			}
			result += "]";
		}
		result += "]";
		return result;
	}
		
}
