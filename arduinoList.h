#ifndef LIST_H
#define LIST_H

template<typename T>
class list {
public:
	list(const unsigned int& i_initialSize) : m_listStackPtr(0), m_listSize(i_initialSize), m_listCount(0), m_list(new T[i_initialSize]){
		
	}
	~list(){
		delete[] m_list;
	}

	void push_back(const T& i_item){
		if(m_listStackPtr < m_listSize){
			m_list[m_listStackPtr] = i_item;
			++m_listCount;
		}
		else{
			T t_list[m_listSize];
			unsigned int t_newListSize = m_listSize + 2;
			for(int i = 0; i < m_listSize; ++i){
				t_list[i] = m_list[i];
			}
			delete[] m_list;
			m_list = new T[t_newListSize];
			for(int i = 0; i < m_listSize; ++i){
				m_list[i] = t_list[i];
			}
			m_list[m_listStackPtr] = i_item;
			m_listSize = t_newListSize;
			++m_listCount;
		}
    ++m_listStackPtr;
	}

  T operator [] (const unsigned int& i_index) {
    return m_list[i_index];
  }
  unsigned int getCount() const {
    return m_listCount;
  }
  unsigned int getSize() const {
    return m_listSize;
  }
  T* getArr() const {
    return m_list;
  }
private:
	T* m_list;
	unsigned int m_listStackPtr;
	unsigned int m_listSize;
	unsigned int m_listCount;
};

#endif