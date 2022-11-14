
%define PTR
%define OFFSET

        section .text


;
; These interrupt services are designs for handling exceptions.
; The IF flag is cleared so that the CPU isn't somehow interrupted from handling an exception.
;

%macro ISRA 1
__ISR_%+%1:
        cli
        push    0
        push    %1
        jmp     ISR_HANDLER
        nop
%endmacro

%macro ISRA_ERRORCODE 1
__ISR_%+%1:
        cli
        push    %1
        jmp     ISR_HANDLER
        nop
%endmacro

ISRA 0
ISRA 1
ISRA 2
ISRA 3
ISRA 4
ISRA 5
ISRA 6
ISRA 7
ISRA_ERRORCODE 8
ISRA 9
ISRA_ERRORCODE 10
ISRA_ERRORCODE 11
ISRA_ERRORCODE 12
ISRA_ERRORCODE 13
ISRA_ERRORCODE 14
ISRA 15
ISRA 16
ISRA_ERRORCODE 17
ISRA 18
ISRA 19
ISRA 20
ISRA 21
ISRA 22
ISRA 23
ISRA 24
ISRA 25
ISRA 26
ISRA 27
ISRA 28
ISRA 29
ISRA_ERRORCODE 30
ISRA 31


;
; These interrupt services are NOT exceptions.
; The IF flag remains.
;

%macro ISRB 1
__ISR_%+%1:
        push    0
        push    %1
        jmp     ISR_HANDLER
        nop
%endmacro

%macro ISRB_ERRORCODE 1
__ISR_%+%1:
        push    %1
        jmp     ISR_HANDLER
        nop
%endmacro

ISRB 32
ISRB 33
ISRB 34
ISRB 35
ISRB 36
ISRB 37
ISRB 38
ISRB 39
ISRB 40
ISRB 41
ISRB 42
ISRB 43
ISRB 44
ISRB 45
ISRB 46
ISRB 47
ISRB 48
ISRB 49
ISRB 50
ISRB 51
ISRB 52
ISRB 53
ISRB 54
ISRB 55
ISRB 56
ISRB 57
ISRB 58
ISRB 59
ISRB 60
ISRB 61
ISRB 62
ISRB 63
ISRB 64
ISRB 65
ISRB 66
ISRB 67
ISRB 68
ISRB 69
ISRB 70
ISRB 71
ISRB 72
ISRB 73
ISRB 74
ISRB 75
ISRB 76
ISRB 77
ISRB 78
ISRB 79
ISRB 80
ISRB 81
ISRB 82
ISRB 83
ISRB 84
ISRB 85
ISRB 86
ISRB 87
ISRB 88
ISRB 89
ISRB 90
ISRB 91
ISRB 92
ISRB 93
ISRB 94
ISRB 95
ISRB 96
ISRB 97
ISRB 98
ISRB 99
ISRB 100
ISRB 101
ISRB 102
ISRB 103
ISRB 104
ISRB 105
ISRB 106
ISRB 107
ISRB 108
ISRB 109
ISRB 110
ISRB 111
ISRB 112
ISRB 113
ISRB 114
ISRB 115
ISRB 116
ISRB 117
ISRB 118
ISRB 119
ISRB 120
ISRB 121
ISRB 122
ISRB 123
ISRB 124
ISRB 125
ISRB 126
ISRB 127
ISRB 128
ISRB 129
ISRB 130
ISRB 131
ISRB 132
ISRB 133
ISRB 134
ISRB 135
ISRB 136
ISRB 137
ISRB 138
ISRB 139
ISRB 140
ISRB 141
ISRB 142
ISRB 143
ISRB 144
ISRB 145
ISRB 146
ISRB 147
ISRB 148
ISRB 149
ISRB 150
ISRB 151
ISRB 152
ISRB 153
ISRB 154
ISRB 155
ISRB 156
ISRB 157
ISRB 158
ISRB 159
ISRB 160
ISRB 161
ISRB 162
ISRB 163
ISRB 164
ISRB 165
ISRB 166
ISRB 167
ISRB 168
ISRB 169
ISRB 170
ISRB 171
ISRB 172
ISRB 173
ISRB 174
ISRB 175
ISRB 176
ISRB 177
ISRB 178
ISRB 179
ISRB 180
ISRB 181
ISRB 182
ISRB 183
ISRB 184
ISRB 185
ISRB 186
ISRB 187
ISRB 188
ISRB 189
ISRB 190
ISRB 191
ISRB 192
ISRB 193
ISRB 194
ISRB 195
ISRB 196
ISRB 197
ISRB 198
ISRB 199
ISRB 200
ISRB 201
ISRB 202
ISRB 203
ISRB 204
ISRB 205
ISRB 206
ISRB 207
ISRB 208
ISRB 209
ISRB 210
ISRB 211
ISRB 212
ISRB 213
ISRB 214
ISRB 215
ISRB 216
ISRB 217
ISRB 218
ISRB 219
ISRB 220
ISRB 221
ISRB 222
ISRB 223
ISRB 224
ISRB 225
ISRB 226
ISRB 227
ISRB 228
ISRB 229
ISRB 230
ISRB 231
ISRB 232
ISRB 233
ISRB 234
ISRB 235
ISRB 236
ISRB 237
ISRB 238
ISRB 239
ISRB 240
ISRB 241
ISRB 242
ISRB 243
ISRB 244
ISRB 245
ISRB 246
ISRB 247
ISRB 248
ISRB 249
ISRB 250
ISRB 251
ISRB 252
ISRB 253
ISRB 254
ISRB 255

        extern _InterruptHandler

;
;
;

ISR_HANDLER:
        pushad
        push    esp
        call    DWORD PTR _InterruptHandler
        add     esp, 4
        popad
        add     esp, 8
        sti             ; NMI will be enabled regardless of ISR A or B.
        iret


        section .data

        global __ISRTBL

__ISRTBL:
%assign i 0 
%rep 256
        dd __ISR_%+i
%assign i i+1 
%endrep

