//
// DD1388 - Lab 2: The matrix
//

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <array>
#include <cmath>


template <typename T>
class Matrix {

    static_assert(std::is_move_constructible<T>::value, "not move constructible"); // T must be move-constructible */
    static_assert(std::is_move_assignable<T>::value,"not move assignable"); // T must be move-assignable */

public:
    // constructors and assignment operators
    Matrix();
    explicit Matrix(size_t dim);                // added explicit here, check if ok.
    Matrix(size_t rows, size_t cols);
    Matrix(const std::initializer_list<T> & list);

    Matrix(const Matrix<T> & other);                  // Copy constructor
    Matrix(Matrix<T> && other) noexcept;        // Move constructor

    Matrix<T> & operator=(const Matrix<T> & other);     // Copy assignment operator
    Matrix<T> & operator=(Matrix<T> && other) noexcept;     // Move assignment operator
    template<typename Y>
    friend std::istream & operator>>(std::istream & is, Matrix<Y> & m);     // Input operator
    template<typename Y>
    friend std::ostream & operator<<(std::ostream & os, const Matrix<Y> & m);   // Output operator

    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    T & operator()(size_t row, size_t col);         // This is the one that is called when you want to change a value in the matrix.
    const T & operator()(size_t row, size_t col) const;         // This is the one that is called when you want to change a value in the matrix.

    // operators
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;

    void operator*=(const Matrix<T> & other);
    void operator+=(const Matrix<T> & other);
    void operator-=(const Matrix<T> & other);

    // methods
    void reset();

    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // iterators
    typedef T* iterator;

    iterator begin();
    iterator end();

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T * m_vec;
};

// input/output operators
template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m);

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m);

// functions
template<typename T>
Matrix<T> identity(size_t dim);
//Matrix<T> identity(T dim);



//
// Implementations
//

template<typename T>
Matrix<T>::Matrix() 
    :m_rows(0),m_cols(0),m_capacity(0),m_vec(new T[0]()){

    }

template<typename T>
Matrix<T>::Matrix(size_t dim)
    :m_rows(dim),m_cols(dim),m_capacity(dim*dim),m_vec(new T[dim*dim]{})
    {  
        for (size_t i = 0; i < dim*dim; i++){
            m_vec[i] = T();
        }}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    :m_rows(rows),m_cols(cols),m_capacity(rows*cols),m_vec(new T[rows*cols]{}){
    
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list)
/*:  Initialize members here */ {

    double root = sqrt(list.size());
        
        if (floor(root) != root){
            throw std::out_of_range("Not even square!!");
            }
        m_rows=root;
        m_cols = root;
        m_capacity = list.size();
        m_vec = new T[m_capacity]();
        int numb=0;
        for (auto element: list){
            m_vec[numb]=element;
            ++numb;

        }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & other)
    :m_rows(other.m_rows),m_cols(other.m_cols),m_capacity(other.m_capacity),m_vec(new T[other.m_capacity]{}){
    for(size_t a = 0; a < other.m_capacity; a++){
        this->m_vec[a] = other.m_vec[a];
    }
    
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept
    :m_rows(other.m_rows),m_cols(other.m_cols),m_capacity(other.m_capacity),m_vec(other.m_vec) {
        other.m_rows = 0;
        other.m_cols = 0;
        other.m_capacity = 0;
        other.m_vec = nullptr;

}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
    if(&m_vec != &other.m_vec){// handles if eg m1=m1 is sent in.        ##### Should I do this with this == other? instead?
            delete []m_vec;     // Deleting old pointer before assignment of new
            m_rows = other.m_rows;
            m_cols = other.m_cols;
            m_capacity = other.m_capacity;
            m_vec= new T[other.m_capacity]();     // Allocating new memory for new pointer
            for(size_t i = 0; i< other.m_capacity; i++){// Copying memory from old to new pointer.
                this->m_vec[i] = other.m_vec[i];
            }
        }
        return *this;       // Could be usefull to look att memcpy here aswell!
    
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept {
    if (this!= &other){
        delete [] m_vec;
        
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_capacity = other.m_capacity;
        m_vec = other.m_vec;
        // m1 = m2 , code above sets m1s value and pointers to m2 and code below makes default constructor value of m2.
        other.m_rows = 0;
        other.m_cols = 0;
        other.m_capacity = 0;
        other.m_vec = nullptr;

    } //                                          ### SHOULD THESE VALUES BE SET TO DEFAULT?!
    return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete [] m_vec;
    

}

template<typename T>
size_t Matrix<T>::rows() const {

return m_rows;
}

template<typename T>
size_t Matrix<T>::cols() const {    

return m_cols;}

template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) {
    // Implementation goes here
    if ( ( row < 0 || col < 0) || (row >= m_rows || col >= m_cols)){
        throw std::out_of_range("Index out of range");
    }
    return m_vec[m_cols*row + col];
    
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const {
    
    if ((row < 0 || col < 0) || (row >= m_rows || col > m_cols)){
        throw std::out_of_range("Index out of range");
    }
    return m_vec[m_cols*row + col];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const {
    // Implementation goes here

    if(m_cols != other.m_rows){
        throw std::out_of_range("The cols of the first matrix have to be the same as the rows of the second Matrix!!");

    }
    Matrix<T> nMatrix = Matrix<T>(m_rows,other.m_cols);// Allocates new return!! ##### Possible memory leek?

    nMatrix.m_rows = m_rows;    // This is because a 2x3 *3x2 = 2x2 matrix
    nMatrix.m_cols = other.m_cols;
    nMatrix.m_capacity = m_rows*other.m_cols;

    

    for (size_t i = 0; i < m_rows; i++){
        for (size_t j = 0; j < other.m_cols; j++){
            T nValue = T();
            for (size_t k = 0; k < m_cols; k++){
                nValue = this->operator()(i,k) * other.operator()(k,j) + nValue;
            }
            nMatrix(i,j) = nValue;

        }
    }

    return nMatrix;
    }

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const {
    // Implementation goes here

    if (m_cols!= other.m_cols || m_rows !=other.m_rows){
        throw std::out_of_range("The Matrices have to have the same dimentions!");
    }

    
    Matrix<T> nMatrix = Matrix<T>(m_rows,m_cols);// Allocates new return!! ##### Possible memory leek?
    
    int temp = 0;
    for (size_t row = 0; row<m_rows;row++){                        // POSSIBLY HERE!! CHECK!
        for (size_t col = 0; col<m_cols;col++){
            nMatrix(row,col)= this->operator()(row,col)+other.operator()(row,col) ;
        }
    }
     
    return nMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const {
    // Implementation goes here
    if (m_cols!= other.m_cols | m_rows !=other.m_rows){
        throw std::out_of_range("The Matrices have to have the same dimentions!");
    }

    Matrix<T> nMatrix = Matrix<T>(m_rows,m_cols);// Allocates new return!! ##### Possible memory leek?
    
    int temp = 0;
    for (size_t row = 0; row < m_rows ; row++){  
        for (size_t col = 0; col < m_cols ; col++){
            // nMatrix.m_vec[row + col - 2+temp]= this->operator()(row,col)-other.operator()(row,col) ; 
            nMatrix(row,col)= this->operator()(row,col)-other.operator()(row,col) ; 
        }
    }
     
    return nMatrix;
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & other) {
    // Implementation goes here
    *this = operator*(other);
    // Error handling is done by -- operator* --
   
    
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & other) {
    // Implementation goes here
    *this = operator+(other);

}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> & other) {
    // Implementation goes here

    *this = operator-(other);

}

template<typename T>
void Matrix<T>::reset() {
    // Implementation goes here
    delete [] m_vec;
    m_rows = 0;
    m_cols = 0;
    m_capacity = 0;
    m_vec = new T[m_capacity]{};    // allocates new memory with elements set to all zero
}

template<typename T>
void Matrix<T>::insert_row(size_t row) {
    // Implementation goes here
    if((row >= 0 && row <= m_rows)){
        T nrow[m_cols]{};    // row of zeroes created
        T *temp =new T[m_capacity + m_cols];
        int cRow = m_cols;
        int addedRows = 0;


        // Divide the new array into new parts

        for (size_t i = 0; i < m_cols * row; i++){
            temp[i] = m_vec[i];
        }

        for (size_t i = m_cols*row; i < (m_cols*row + m_cols); i++){
            temp[i] = 0;
        }

        for (size_t i = (m_cols*row + m_cols); i < m_capacity+m_cols ;i++){
            temp[i] = m_vec[i-m_cols];
        }
    








        

        delete []m_vec;
        m_rows = m_rows +1; // updating size of rows
        m_capacity = m_capacity + m_cols;   // updating size of capacity
        m_vec = temp;
        temp = nullptr; // helps us so the deconstructor does not delete new array.// helps us so the deconstructor does not delete new array.
    }
    else{
        throw std::out_of_range("Index out of range");
    }
}

template<typename T>
void Matrix<T>::append_row(size_t row) {
    // Implementation goes here
    insert_row(row + 1);

    }


template<typename T>
void Matrix<T>::remove_row(size_t row) {
    // Implementation goes here

    if(row >= m_rows || row < 0){throw std::out_of_range("Index out of range");}

      T nrow[m_cols]{};    // row of zeroes created
    T *temp =new T[m_capacity - m_cols];    // new vector will be shorter.
    
    
    
    
    
    
    int a = 1;
   
    int skippedE = 0;
    int newIndex = 0;
    for (size_t i = 0; i < m_capacity;i++){
        int t_value = m_cols*row - m_cols*a;
        if (t_value < 0 && i == 0){
            skippedE = m_cols;
        }

        if ((m_cols*row) == i){

            skippedE = m_cols;
            }
        if (skippedE == 0){
            temp[newIndex]=m_vec[i];
            newIndex++;
            }
        if(skippedE != 0)
        {
            skippedE = skippedE -1;
        }
    }
    delete []m_vec;
        m_rows = m_rows -1;
        m_capacity =m_capacity - m_cols;
        m_vec = temp;
        temp = nullptr;
    
    }

template<typename T>
void Matrix<T>::insert_column(size_t col) {

    // Implementation goes here
    if(col < 0 || (col > m_cols)){
    // if ((col < 0) || (col > m_cols) ){
        throw std::out_of_range("Index out of range");
    }


     else{
    T ncol[1]{};
    T *temp =new T[m_capacity + m_rows];
    size_t added = 0;
    size_t correction = 0;

    for (size_t i = 0; i < m_capacity + m_rows ; i++){

        
        if((i) == (added*m_cols+col+added)){
            temp[i]=ncol[0];
            
            added++;
        }
        else{
            temp[i] =m_vec[i-added] ;
        }


    }
    delete []m_vec;
    m_cols = m_cols +1;
    m_capacity = m_capacity + m_rows;
    m_vec = temp;
    temp = nullptr;
    }
    
}

template<typename T>
void Matrix<T>::append_column(size_t col) {
    // Implementation goes here
    insert_column(col+1);
    
}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    // Implementation goes here
    if(col >= m_cols || col < 0){throw std::out_of_range("Index out of range");}
    
    T *temp =new T[m_rows*(m_cols-1)];        
    size_t added = 0;
    size_t correction = col;

    size_t nIndex = 0;
    for(size_t i = 0; i < m_capacity; i++){

        
        if ((i) == (correction)){
            correction = correction + m_cols;

            }
        else{
            temp[nIndex]=m_vec[i];
            nIndex++;
        }
    
    }
    delete []m_vec;
    m_cols = m_cols -1;
    m_capacity = m_capacity - m_rows;
    m_vec = temp;
    temp =nullptr;
    
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    // Implementation goes here
    return m_vec;
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() {
    // Implementation goes here
    
    //return m_vec + m_capacity -1;
    return m_vec + m_capacity;

}

template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m) {
    // Implementation goes here
    int rows,cols;
    is >> rows;
    is >> cols;
    m = Matrix<T>(rows,cols);


   
    



    for(int i = 0; i<m.m_capacity;i++){
        is >>m.m_vec[i];
    }
    return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    // Implementation goes here
    int ref = 0;
    os << m.rows() << " " << m.cols() << "\n";

while (ref<m.m_capacity)
{   
    
    
    // os << m.m_vec[ref]<< " ";
    if ( ((ref+1)%m.m_cols == (m.m_capacity%m.m_cols))&& ref !=0){
        
        os << m.m_vec[ref]<< "\n";
    }
    
    else{os << m.m_vec[ref]<< " ";}
    ++ref;
    
        
    
}


return os;
}

template<typename T>
//Matrix<T> identity(T dim) 
Matrix<T> identity(size_t dim)
 {
    if (dim < 0){
        throw std::out_of_range("Dimension has to be positive!");
    }
    // Implementation goes here
     Matrix<T> m = Matrix<T>(dim) ;   // should return a empty Matrix
    for(size_t i = 0; i < dim; i++) {
        for(size_t j = 0; j < dim; j++) {
            if (i == j) {
                m(i, j) = 1; // Set diagonal elements to 1
            }
             else {
                 m(i, j) = 0; // Set off-diagonal elements to 0
             }
        }
    }
    return m;
}



#endif //MATRIX_H
