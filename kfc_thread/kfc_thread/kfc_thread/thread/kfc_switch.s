#if defined(__x86_64__)

.text
.global __kfc_first_switch

__kfc_first_switch:
# 上下文保护

    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %r11
    pushq %r10
    pushq %r9
    pushq %r8

    pushq %rbp
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    pushq %rbx
    pushq %rax

# save %rsp
    movq %rdi,%rax
    movq %rsp,(%rax)

# 上下文恢复
# restore %rsp
    movq (%rsi),%rsp
    movq $0x1,8(%rsi)

    popq %rax
    popq %rbx
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    popq %rbp

    popq %r8
    popq %r9
    popq %r10
    popq %r11
    popq %r12
    popq %r13
    popq %r14
    popq %r15


#   如果是子线程第一次调用
#   获取参数

    movq 16(%rsp),%rdi
    movq 24(%rsp),%rsi

#   移动栈指针 清理栈
    movq (%rsp),%rax
    movq %rax,24(%rsp)
    addq $24,%rsp
    ret

.global __kfc_switch

__kfc_switch:
    # 上下文保护

    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %r11
    pushq %r10
    pushq %r9
    pushq %r8
    pushq %rbp
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    pushq %rbx
    pushq %rax

    # save %rsp
    movq %rdi,%rax
    movq %rsp,(%rax)

    # 上下文恢复
    # restore %rsp
    movq (%rsi),%rsp

    popq %rax
    popq %rbx
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    popq %rbp
    popq %r8
    popq %r9
    popq %r10
    popq %r11
    popq %r12
    popq %r13
    popq %r14
    popq %r15

    ret


.global __kfc_died_switch

__kfc_died_switch:
    # 上下文恢复
    # restore %rsp
    movq (%rdi),%rsp

    popq %rax
    popq %rbx
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    popq %rbp
    popq %r8
    popq %r9
    popq %r10
    popq %r11
    popq %r12
    popq %r13
    popq %r14
    popq %r15

    ret

.global __kfc_died_first_switch

__kfc_died_first_switch:
    # 上下文恢复
    # restore %rsp
    movq (%rdi),%rsp
    movq $0x1,8(%rdi)

    popq %rax
    popq %rbx
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    popq %rbp

    popq %r8
    popq %r9
    popq %r10
    popq %r11
    popq %r12
    popq %r13
    popq %r14
    popq %r15


    #   如果是子线程第一次调用
    #   获取参数

    movq 16(%rsp),%rdi
    movq 24(%rsp),%rsi

    #   移动栈指针 清理栈
    movq (%rsp),%rax
    movq %rax,24(%rsp)
    addq $24,%rsp
    ret

#endif
