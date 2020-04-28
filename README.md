# LinuxKernelModule

### Thành viên:

- Nguyễn Quý Thanh - 18127210.
- Nguyễn Thị Tâm Phúc - 18127182.
- Nguyễn Phạm Thanh Vy - 18127258 (đang nằm viện - đã xin phép).

### Yêu cầu:

- Tìm hiểu về Linux Kernel Module.
- Tìm hiểu về hệ thống quản lý file và device trong linux.
- Giao tiếp giữa tiến trình ở user space và kernel space.

### Kết quả:

- Module sinh ra một số ngẫu nhiên.
- Tạo một character device cho phép tiến trình ở user space có thể open và read các số ngẫu nhiên.

### Môi trường sử dụng:

- Ubuntu 20.04 LTS.
- Kernel phiên bản 5.4.0-26-generic.
- Ngôn ngữ C với các thư viện hỗ trợ của Linux.
- Cài đặt thêm gói ***build-essential*** bằng lệnh `sudo apt-get install build-essential`.

### Hướng dẫn sử dụng module:

**1. Cách 1: sử dụng lệnh make all**
- Mở terminal và `cd` vào thư mục chứa source code.
- Chạy lệnh `make all`.
- Cài đặt module bằng lệnh `sudo insmod Random.ko`.
- Xem số ngẫu nhiên được sinh ra bằng lệnh `sudo cat /dev/Random`.
- Gỡ cài đặt module bằng lệnh `sudo rmmod Random`.
- Chạy lệnh `dmesg` để xem các bước thực hiện của module.

**2. Cách 2: sử dụng lệnh make auto**
- Mở terminal và `cd` vào thư mục chứa source code.
- Chạy lệnh `make auto` để thực hiện tự động toàn bộ các bước bên trên.
- Chạy lệnh `dmesg` để xem các bước thực hiện của module.
