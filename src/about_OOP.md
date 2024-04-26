- Tính đóng gói (Encapsulation): Thực hiện cho tất cả các object trong chương trình, thông số của chúng đều được để private, đảm bảo được truy cập qua hàm get và thay đổi qua hàm set.

- Tính kế thừa (Inheritance): Sử dụng kế thừa để đơn giản hóa việc tạo ra các object mới, tái sử dụng mã nguồn từ lớp cha. Các lớp trong chương trình thực hiện kế thừa `public`.
  + Các object trong game sử dụng nằm tại các folder: [Spell](./Spell), [Model](./Model/), [EnemyObject](./EnemyObject/), [PlayerObject](./PlayerObject/).

- Tính đa hình (Polymorphism): một phương thức có thể có nhiều các thực hiện khác nhau tùy vào đối tượng thực hiện nó. (C++ dùng từ khóa `virtual` để thực hiện tính đa hinh).
  + Ví dụ cụ thể nhất là các đối tượng barrer kngiht, droid zapper, vagabond, archer đều sở hữu các phương thức giống nhau nhưng khi thực hiện khác nhau. Tìm hiểu thêm trong folder: [EnemyObject](./EnemyObject/).

- Tính trừu tượng(Abstraction): tạo các base -> model -> object, định nghĩa các phương thức chung tại lớp base, các lớp con triển khai cụ thể cho từng đối tượng.
  + Lớp base trong chương trình: [BaseState](./States/BaseState.h), [BaseGenerator](./Factory/BaseGenerator.h), [BaseObject](./Model/BaseObject.h)