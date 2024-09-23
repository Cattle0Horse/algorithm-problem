namespace OI::Chars {
bool isUpper(char c) {
    return (c & 32) == 0;
}
bool isLower(char c) {
    return (c & 32) != 0;
}
// 'a' => 0
int toIndex(char c) {
    return (c & 31) - 1;
}
char toLower(char c) {
    return c |= 32;
}
char toUpper(char c) {
    return c & 95;
}
// 'a' => 'A'
// 'A' => 'a'
char toggleCase(char c) {
    return c ^ 32;
}
} // namespace OI::Chars