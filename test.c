#include "libasm.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>


void test_result(const char *test_name, int success) {
    printf("%-30s: %s%s%s\n", test_name, 
           success ? GREEN "PASS" : RED "FAIL", 
           RESET, 
           success ? "" : " ❌");
}


void test_strlen() {
    printf("\n=== Testing ft_strlen ===\n");
    
    const char *test_strings[] = {
        "",
        "Hello",
        "This is a longer string",
        "Contains\0hidden\0nulls",
        "Special chars: \n\t\r"
    };
    
    int success = 1;
    for (size_t i = 0; i < sizeof(test_strings)/sizeof(char*); i++) {
        size_t lib_len = strlen(test_strings[i]);
        size_t ft_len = ft_strlen(test_strings[i]);
        success &= (lib_len == ft_len);
        printf("String: \"%s\"\n", test_strings[i]);
        printf("strlen: %zu, ft_strlen: %zu\n", lib_len, ft_len);
    }
    test_result("ft_strlen", success);
}


void test_strcpy() {
    printf("\n=== Testing ft_strcpy ===\n");
    
    const char *test_strings[] = {
        "",
        "Hello",
        "This is a test string",
        "Special\nchars\tincluded"
    };
    
    int success = 1;
    for (size_t i = 0; i < sizeof(test_strings)/sizeof(char*); i++) {
        char buf1[BUFFER_SIZE] = {0};
        char buf2[BUFFER_SIZE] = {0};
        
        strcpy(buf1, test_strings[i]);
        char *ft_result = ft_strcpy(buf2, test_strings[i]);
        
        success &= (strcmp(buf1, buf2) == 0);
        success &= (ft_result == buf2);
        
        printf("Original: \"%s\"\n", test_strings[i]);
        printf("strcpy: \"%s\", ft_strcpy: \"%s\"\n", buf1, buf2);
    }
    test_result("ft_strcpy", success);
}

void test_strcmp() {
    printf("\n=== Testing ft_strcmp ===\n");
    
    struct {
        const char *s1;
        const char *s2;
    } test_pairs[] = {
        {"", ""},
        {"Hello", "Hello"},
        {"Hello", "World"},
        {"ABC", "ABCD"},
        {"ABCD", "ABC"},
        {"", "notempty"},
        {"notempty", ""}
    };
    
    int success = 1;
    for (size_t i = 0; i < sizeof(test_pairs)/sizeof(test_pairs[0]); i++) {
        int lib_result = strcmp(test_pairs[i].s1, test_pairs[i].s2);
        int ft_result = ft_strcmp(test_pairs[i].s1, test_pairs[i].s2);
        
        // Convert to -1, 0, 1 for comparison
        lib_result = (lib_result > 0) - (lib_result < 0);
        ft_result = (ft_result > 0) - (ft_result < 0);
        
        success &= (lib_result == ft_result);
        
        printf("Comparing \"%s\" with \"%s\"\n", test_pairs[i].s1, test_pairs[i].s2);
        printf("strcmp: %d, ft_strcmp: %d\n", lib_result, ft_result);
    }
    test_result("ft_strcmp", success);
}


void test_write() {
    printf("\n=== Testing ft_write ===\n");
    
    const char *test_str = "Test string for write\n";
    size_t len = strlen(test_str);
    int success = 1;
    
    // Test normal write
    ssize_t lib_result = write(1, test_str, len);
    ssize_t ft_result = ft_write(1, test_str, len);
    success &= (lib_result == ft_result);
    
    // Test error case (invalid fd)
    errno = 0;
    lib_result = write(-1, test_str, len);
    int lib_errno = errno;
    
    errno = 0;
    ft_result = ft_write(-1, test_str, len);
    int ft_errno = errno;
    
    success &= (lib_result == ft_result && lib_errno == ft_errno);
    
    printf("Normal write - lib: %zd, ft: %zd\n", lib_result, ft_result);
    printf("Error case - lib errno: %d, ft errno: %d\n", lib_errno, ft_errno);
    
    test_result("ft_write", success);
}


void test_read() {
    printf("\n=== Testing ft_read ===\n");
    
    char lib_buf[BUFFER_SIZE] = {0};
    char ft_buf[BUFFER_SIZE] = {0};
    int success = 1;
    
    // Create a test file
    const char *test_str = "Test string for read\n";
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, test_str, strlen(test_str));
    close(fd);
    
    // Test normal read
    fd = open("test.txt", O_RDONLY);
    ssize_t lib_result = read(fd, lib_buf, 99);
    close(fd);
    
    fd = open("test.txt", O_RDONLY);
    ssize_t ft_result = ft_read(fd, ft_buf, 99);
    close(fd);
    
    success &= (lib_result == ft_result && strcmp(lib_buf, ft_buf) == 0);
    
    // Test error case (invalid fd)
    errno = 0;
    lib_result = read(-1, lib_buf, 99);
    int lib_errno = errno;
    
    errno = 0;
    ft_result = ft_read(-1, ft_buf, 99);
    int ft_errno = errno;
    
    success &= (lib_result == ft_result && lib_errno == ft_errno);
    
    printf("Normal read - lib: %zd, ft: %zd\n", lib_result, ft_result);
    printf("Read content - lib: \"%s\", ft: \"%s\"\n", lib_buf, ft_buf);
    printf("Error case - lib errno: %d, ft errno: %d\n", lib_errno, ft_errno);
    
    unlink("test.txt");  // Clean up test file
    test_result("ft_read", success);
}


void test_strdup() {
    printf("\n=== Testing ft_strdup ===\n");
    
    const char *test_strings[] = {
        "",
        "Hello",
        "This is a longer test string",
        "Special\nchars\tincluded"
    };
    
    int success = 1;
    for (size_t i = 0; i < sizeof(test_strings)/sizeof(char*); i++) {
        char *lib_result = strdup(test_strings[i]);
        char *ft_result = ft_strdup(test_strings[i]);
        
        success &= (strcmp(lib_result, ft_result) == 0);
        
        printf("Original: \"%s\"\n", test_strings[i]);
        printf("strdup: \"%s\", ft_strdup: \"%s\"\n", lib_result, ft_result);
        
        free(lib_result);
        free(ft_result);
    }
    test_result("ft_strdup", success);
}

int main() {
    printf("=== LibASM Tests ===\n");
    
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    
    return 0;
}