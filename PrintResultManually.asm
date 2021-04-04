include Irvine32.inc

.data
	price1 dword 7766
	price2 dword 87654
  
	qty1 dword 2
	qty2 dword 7
  
	percent dword 100
  
	fullStop byte ".", 0
	showPrice byte "Price is ", 0
	showQty byte "Qty is ", 0

	quotient dword ?
	remainder dword ?
.code

main PROC
;; Print Price & Qty for User
	mov edx, offset showPrice
	call WriteString
  
	mov eax, price1
	call WriteDec
  
	mov al, '('
	call WriteChar
  
	mov edx, 0
	mov eax, 0
	mov eax, price1
	mov ebx, percent
	div ebx
	mov quotient, eax
	mov remainder, edx
  
	mov eax, quotient
	call WriteDec
  
	mov edx, offset fullStop
	call writestring
  
	mov eax, remainder
	call WriteDec
  
	mov al, ')'
	call WriteChar
	call crlf

	mov edx, offset showQty
	call writestring
	mov eax, qty1
	call WriteDec
	call crlf
  
;; Calculation Here
	mov eax, price1
	mov ebx, qty1
	mul ebx
	div percent
	mov quotient, eax
	mov remainder, edx

;;Print Result
	mov eax, quotient
	call WriteDec

	mov edx, offset fullStop
	call writestring

	mov eax, remainder
	call WriteDec
	call crlf
	call crlf


;;2nd Example From Here
	mov edx, offset showPrice
	call writestring
	mov eax, price2
	call WriteDec
	mov al, '('
	call WriteChar
	mov edx, 0
	mov eax, 0
	mov eax, price2
	mov ebx, percent
	div ebx
	mov quotient, eax
	mov remainder, edx
	mov eax, quotient
	call WriteDec
	mov edx, offset fullStop
	call writestring
	mov eax, remainder
	call WriteDec
	mov al, ')'
	call WriteChar
	call crlf

	mov edx, offset showQty
	call writestring
	mov eax, qty2
	call WriteDec
	call crlf

	mov eax, price2
	mov ebx, qty2
	mul ebx
	div percent
	mov quotient, eax
	mov remainder, edx

	mov eax, quotient
	call WriteDec

	mov edx, offset fullStop
	call writestring

	mov eax, remainder
	call WriteDec

	Exit
main ENDP
