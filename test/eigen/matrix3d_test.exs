defmodule Matrix3dTest do
  use ExUnit.Case, async: true

  alias Eigen.Matrix3d

  describe "new" do
    test "initializes a struct with a pointer to C memory" do
      matrix3d = Matrix3d.new()
      assert %Matrix3d{__reference__: reference} = matrix3d
      assert reference |> is_reference()
    end
  end

  describe "to_list" do
    test "uses a reference to create a list of lists" do
      matrix_list = [[1.0, 5.0, 10.0], [4.0, 8.0, 12.0], [7.0, 14.0, 21.0]]
      matrix3d = Matrix3d.new(matrix_list)

      assert matrix3d |> Matrix3d.to_list() == [
               [1.0, 5.0, 10.0],
               [4.0, 8.0, 12.0],
               [7.0, 14.0, 21.0]
             ]
    end
  end
end
