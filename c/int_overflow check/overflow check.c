if(ans > INT_MAX / 10 || (ans == INT_MAX / 10 && digit > 7)) {
    return 0; // Overflow
}
else if(ans < INT_MIN / 10 || (ans == INT_MIN / 10 && digit < -8)) {
    return 0; // Underflow
}