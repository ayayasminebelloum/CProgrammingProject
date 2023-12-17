Const char *sampleCode = “””
					x = 10
					y = 3
					
					//DEFINE add(x,y)
					//	RETURN x+y
					sum = ADD(x,y)
					//sum = sum(x,y)
					PRINT “Sum: “ + sum


//DEFINE multiply(x,y)
					//	RETURN x*y
					product = MULT(x,y)
					//product = multiply(x,y)
					PRINT “Product: “ + product


//DEFINE subtract(x,y)
					//	RETURN x-y
					difference = SUB(x,y)
					//difference = subtract(x,y)
					PRINT “Difference: “ + difference 

“””



Const char *sampleCode = “””
				timer = 10

				WHILE timer > 0
					IF timer % 2 EQUAL 0 THEN
						PRINT counter + “ is even”
					ELSE 
						PRINT counter + “ is odd”
					
					counter = SUBTRACT(counter, 1)
						
					“””
