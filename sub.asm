INCLUDE Irvine32.inc

setItemTotal PROTO C, value:real8
SetSubTotal PROTO C, value:real8
DisplayPaymentCart PROTO C, value:real8, value:real8, value:real8

.data

newItemPriceTotal real8 ?
itemTotal real8 ?
doubleSubTotal REAL8 0.0
zeroZero Real8 0.0
percentage REAL8 100.00

; 6% Sales Tax
SST REAL8 6.0
calculatedSST REAL8 ?

; 10% Service Charge
SCH REAL8 10.0
calculatedSCH REAL8 ?

; Total after Tax and Service Charge
calculatedTax REAL8 ?
calculatedTotal REAL8 ?

.code

CalculateItemTotal PROC C price:real8, qty:real8

	fld price
	fmul qty
	fstp itemTotal

	INVOKE setItemTotal, itemTotal

	ret
CalculateItemTotal ENDP

GetNewItemPrice PROC C price1:real8, price2:real8
	fld price1
	fadd price2
	fstp newItemPriceTotal
	INVOKE setItemTotal, newItemPriceTotal

	ret
GetNewItemPrice ENDP

GetNewItemQty PROC C qty1:dword, qty2:dword
	xor eax, eax
	
	mov eax, qty1
	add eax, qty2

	ret
GetNewItemQty ENDP

CalculateSubTotal PROC C, len:dword, arr:real8
	
	mov eax, len
	test eax, eax		
	jnz cont					; check if array size is 0
	ret

	cont:
		fld zeroZero			;push 0 inside the stack
		fstp doubleSubTotal		;pop the stack and store inside doubleSubTotal

		mov esi, 0				;holds index for array
		mov ecx, len			;stores the array size
		xor eax, eax			;empty the register

		L1:
			push ecx

			fld arr[esi]		;store index data inside stack
			fadd doubleSubTotal	;add stack with variable
			fstp doubleSubTotal	;pop the stack and store inside the variable
			add esi, type arr	;next index

			pop ecx				;restore our counter
			loop l1
		
		INVOKE SetSubTotal, doubleSubTotal

	ret
CalculateSubTotal ENDP

CalculateTotal PROC C subTotal:REAL8
	;1. calculatedSST

	fld SST					;Load sst and push it to stack
	fdiv percentage			;divide the stack(SST) with percentage(100)
	fmul subTotal			;multiply the stack(SSL/100) with subTotal
	fstp calculatedSST		;pop the stack and store inside calculatedSST
	

	;2. calculatedSCH

	fld SCH
	fdiv percentage
	fmul subTotal
	fstp calculatedSCH


	;3. calculatedTotal

	fld calculatedSCH
	fadd calculatedSST
	fadd subTotal
	fstp calculatedTotal

	INVOKE DisplayPaymentCart, calculatedSST, calculatedSCH, calculatedTotal
	ret
CalculateTotal ENDP

MinusOne PROC C intVal:dword
	xor eax, eax

	mov eax, intVal
	sub eax, 1

	ret
MinusOne ENDP

GetMinusTwoVal PROC C val1:dword, val2:dword
	xor eax, eax

	mov eax, val1
	sub eax, val2

	ret
GetMinusTwoVal ENDP

END
