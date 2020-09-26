template<typename T>
class Queue
{
private:
    int m_capacity;
    int m_size;
    int m_startIndex;
    int m_endIndex;
    T* m_buffer;
 
    void expand_queue() {
        int newCapacity = m_capacity * 2;
        T* newBuffer = new T[newCapacity];
        if (m_endIndex <= m_startIndex) {
            int cnt = 0;
            for (int i = m_startIndex; i < m_capacity; i++) {
                newBuffer[cnt++] = m_buffer[i];
            }
 
            for (int i = 0; i < m_endIndex; i++) {
                newBuffer[cnt++] = m_buffer[i];
            }
        } else {
            int cnt = 0;
            for (int i = m_startIndex; i < m_endIndex; i++) {
                newBuffer[cnt++] = m_buffer[i];
            }            
        }
 
        delete[] m_buffer;
        m_buffer = newBuffer;
        m_startIndex = 0;
        m_endIndex = m_size;
        m_capacity = newCapacity;
    }
 
    void init_queue(int capacity) {
        m_capacity = capacity;
        m_size = 0;
        m_startIndex = 0;
        m_endIndex = 0;
 
        m_buffer = new T[capacity];
    }
 
public:
    Queue() {
        init_queue(32);
    }
 
    Queue(int capacity) {
        init_queue(capacity);
    }
 
    void push(T element) {
        if (m_endIndex == m_startIndex && m_size > 0) {
            // expand queue
            expand_queue();
        }
 
        m_buffer[m_endIndex] = element;
        m_endIndex = (m_endIndex + 1) % m_capacity;
        m_size++;
    }
 
    void pop() {
        if (m_size == 0) {
            return;
        }
 
        m_startIndex = (m_startIndex + 1) % m_capacity;
        m_size--;
    }
 
    T front() {
        if (m_size == 0) {
            throw;
        }
 
        return m_buffer[m_startIndex];
    }
 
    T back() {
        if (m_size == 0) {
            throw;
        }
 
        if (m_endIndex == 0) {
            return m_buffer[m_capacity - 1];
        } else {
            return m_buffer[m_endIndex - 1];
        }
    }
	bool empty(){
		return m_size==0;
	}
    int size() {
        return m_size;
    }
};