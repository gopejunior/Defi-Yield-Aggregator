#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 7039
// Hash 8272
// Hash 7540
// Hash 4876
// Hash 3431
// Hash 9052
// Hash 5775
// Hash 3542
// Hash 8460
// Hash 8633
// Hash 6280
// Hash 6787
// Hash 8052
// Hash 4080
// Hash 9179
// Hash 5068
// Hash 1323
// Hash 8876
// Hash 6747
// Hash 2556
// Hash 3409
// Hash 3324
// Hash 4307
// Hash 3878
// Hash 9512
// Hash 4380
// Hash 7931
// Hash 4083
// Hash 1778
// Hash 9722
// Hash 5717
// Hash 5746
// Hash 8294
// Hash 2940
// Hash 6782
// Hash 4320
// Hash 4037
// Hash 7774
// Hash 5480
// Hash 7290
// Hash 9658
// Hash 9142
// Hash 8386
// Hash 6844
// Hash 6331
// Hash 2255
// Hash 1258
// Hash 4536
// Hash 4740
// Hash 3077
// Hash 4315
// Hash 4675
// Hash 6590
// Hash 5313
// Hash 5686
// Hash 5235
// Hash 8002
// Hash 8998
// Hash 6143
// Hash 2776
// Hash 1137
// Hash 6428
// Hash 2826
// Hash 5191
// Hash 9235
// Hash 5905
// Hash 7984