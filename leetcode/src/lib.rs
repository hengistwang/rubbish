use std::cmp::max;
use std::cmp::min;
use std::collections::BinaryHeap;
use std::collections::HashMap;
use std::collections::VecDeque;

struct Solution;

// https://leetcode.cn/problems/two-sum
impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut m = HashMap::new();
        for (i, num) in nums.iter().enumerate() {
            if m.contains_key(&(target - num)) {
                return vec![*m.get(&(target - num)).unwrap(), i as i32];
            } else {
                m.insert(num, i as i32);
            }
        }
        vec![]
    }
}
// https://leetcode.cn/problems/kth-largest-element-in-an-array
impl Solution {
    pub fn find_kth_largest(nums: Vec<i32>, k: i32) -> i32 {
        let mut bh = BinaryHeap::new();
        for i in nums {
            bh.push(i);
        }
        for i in 0..k {
            bh.pop();
        }
        *bh.peek().unwrap()
    }
}
// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock
impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let mut min = i32::MAX;
        let mut profit = i32::MIN;
        for num in prices {
            if num < min {
                min = num;
            }
            if num - min > profit {
                profit = num - min;
                println!("{}", num - min);
            }
        }
        profit
    }
}
// https://leetcode.cn/problems/valid-parentheses
impl Solution {
    pub fn is_valid(s: String) -> bool {
        let mut vd = VecDeque::new();
        for i in s.chars() {
            if (i == '}' || i == ')' || i == ']') && vd.is_empty() {
                return false;
            }
            if i == '}' && *vd.back().unwrap() == '{' {
                vd.pop_back();
            } else if i == ')' && *vd.back().unwrap() == '(' {
                vd.pop_back();
            } else if i == ']' && *vd.back().unwrap() == '[' {
                vd.pop_back();
            } else {
                vd.push_back(i);
            }
        }
        vd.is_empty()
    }
}
// https://leetcode.cn/problems/trapping-rain-water
impl Solution {
    pub fn trap(height: Vec<i32>) -> i32 {
        let mut left_max = Vec::with_capacity(height.len());
        let mut right_max = Vec::with_capacity(height.len());
        let mut max = i32::MIN;
        for i in height.iter() {
            if *i > max {
                max = *i;
            }
            left_max.push(max);
        }
        max = i32::MIN;
        for i in height.iter().rev() {
            if *i > max {
                max = *i;
            }
            right_max.push(max);
        }
        right_max.reverse();
        let mut ans = 0;
        for (i, value) in height.iter().enumerate() {
            ans += min(left_max.get(i).unwrap(), right_max.get(i).unwrap()) - value;
        }
        ans
    }
}
// https://leetcode.cn/problems/longest-substring-without-repeating-characters
impl Solution {
    pub fn length_of_longest_substring(s: String) -> i32 {
        let mut vd = VecDeque::new();
        let mut ans = 0;
        for i in s.chars() {
            if vd.contains(&i) {
                ans = max(ans, vd.len() as i32);
                while *vd.front().unwrap() != i {
                    vd.pop_front();
                }
                vd.pop_front();
            }
            vd.push_back(i);
        }
        max(ans, vd.len() as i32)
    }
}
// https://leetcode.cn/problems/maximum-subarray
impl Solution {
    // TODO  divide algorithm
    pub fn max_sub_array(nums: Vec<i32>) -> i32 {
        let mut pre = 0;
        let mut ans = i32::MIN;
        for num in nums {
            println!("{}", num);
            pre = max(pre + num, num);
            ans = max(ans, pre);
        }
        ans
    }
}
// https://leetcode.cn/problems/edit-distance
impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        if word1.is_empty() {
            return word2.len() as i32;
        }
        if word2.is_empty() {
            return word1.len() as i32;
        }
        let x = word1.len() + 1;
        let y = word2.len() + 1;
        let word1 = word1.as_bytes();
        let word2 = word2.as_bytes();
        let mut arr = vec![0; (x * y)];
        for i in 0..x {
            for j in 0..y {
                if 0 == i {
                    arr[i * y + j] = j;
                } else if 0 == j {
                    arr[i * y + j] = i;
                } else {
                    let mut cost = 0;
                    if word1[(i - 1) as usize] == word2[(j - 1) as usize] {
                        cost = 0;
                    } else {
                        cost = 1;
                    }
                    let temp = min(
                        min(arr[(i - 1) * y + j], arr[i * y + j - 1]) + 1,
                        arr[(i - 1) * y + j - 1] + cost,
                    );
                    arr[i * y + j] = temp;
                }
            }
        }
        println!("{:?}", arr);
        arr[(x - 1) * y + y - 1] as i32
    }
}
