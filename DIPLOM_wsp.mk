.PHONY: clean All

All:
	@echo ----------Building project:[ Sample1 - Debug ]----------
	@cd "Sample1" && "mingw32-make.exe"  -j 4 -f "Sample1.mk"
clean:
	@echo ----------Cleaning project:[ Sample1 - Debug ]----------
	@cd "Sample1" && "mingw32-make.exe"  -j 4 -f "Sample1.mk" clean
