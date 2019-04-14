defmodule Eigen.Matrix3dTest do
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
      matrix3d =
        [
          [1.0, 5.0, 10.0],
          [4.0, 8.0, 12.0],
          [7.0, 14.0, 21.0]
        ]
        |> Matrix3d.new()

      assert matrix3d |> Matrix3d.to_list() == [
               [1.0, 5.0, 10.0],
               [4.0, 8.0, 12.0],
               [7.0, 14.0, 21.0]
             ]
    end

    test "returns {:error, message} when the reference is not found" do
      bad_ref = :erlang.list_to_ref('#Ref<0.4192537678.4073193475.71181>')
      matrix = %Matrix3d{__reference__: bad_ref}

      assert {:error, "unable to reference pointer"} = matrix |> Matrix3d.to_list()
    end
  end

  describe "mult with scalar" do
    test "multiplies the matrix by a float, returning a new pointer" do
      first_matrix3d =
        [
          [1.0, 5.0, 10.0],
          [4.0, 8.0, 12.0],
          [7.0, 14.0, 21.0]
        ]
        |> Matrix3d.new()

      {:ok, second_matrix3d} =
        first_matrix3d
        |> Matrix3d.mult(2.0)

      assert first_matrix3d.__reference__ != second_matrix3d.__reference__

      assert second_matrix3d |> Matrix3d.to_list() == [
               [2.0, 10.0, 20.0],
               [8.0, 16.0, 24.0],
               [14.0, 28.0, 42.0]
             ]
    end

    test "returns {:error, message} when the multiplier is not a float" do
      assert {:error, "multiplier must be a float"} =
               [
                 [1.0, 5.0, 10.0],
                 [4.0, 8.0, 12.0],
                 [7.0, 14.0, 21.0]
               ]
               |> Matrix3d.new()
               |> Matrix3d.mult("seven")

      assert {:error, "multiplier must be a float"} =
               [
                 [1.0, 5.0, 10.0],
                 [4.0, 8.0, 12.0],
                 [7.0, 14.0, 21.0]
               ]
               |> Matrix3d.new()
               |> Matrix3d.mult(12)
    end

    test "returns {:error, message} when the reference is not found" do
      bad_ref = :erlang.list_to_ref('#Ref<0.4192537678.4073193475.71181>')
      matrix = %Matrix3d{__reference__: bad_ref}

      assert {:error, "unable to reference pointer"} = matrix |> Matrix3d.mult(1.0)
    end
  end

  describe "div with scalar" do
    test "divides the matrix by a float, returning a new pointer" do
      first_matrix3d =
        [
          [1.0, 5.0, 10.0],
          [4.0, 8.0, 12.0],
          [7.0, 14.0, 21.0]
        ]
        |> Matrix3d.new()

      {:ok, second_matrix3d} =
        first_matrix3d
        |> Matrix3d.div(2.0)

      assert first_matrix3d.__reference__ != second_matrix3d.__reference__

      assert second_matrix3d |> Matrix3d.to_list() == [
               [0.5, 2.5, 5.0],
               [2.0, 4.0, 6.0],
               [3.5, 7.0, 10.5]
             ]
    end

    test "returns {:error, message} when the divisor is not a float" do
      assert {:error, "divisor must be a float"} =
               [
                 [1.0, 5.0, 10.0],
                 [4.0, 8.0, 12.0],
                 [7.0, 14.0, 21.0]
               ]
               |> Matrix3d.new()
               |> Matrix3d.div("seven")

      assert {:error, "divisor must be a float"} =
               [
                 [1.0, 5.0, 10.0],
                 [4.0, 8.0, 12.0],
                 [7.0, 14.0, 21.0]
               ]
               |> Matrix3d.new()
               |> Matrix3d.div(12)
    end

    test "returns {:error, message} when the reference is not found" do
      bad_ref = :erlang.list_to_ref('#Ref<0.4192537678.4073193475.71181>')
      matrix = %Matrix3d{__reference__: bad_ref}

      assert {:error, "unable to reference pointer"} = matrix |> Matrix3d.div(1.0)
    end
  end
end
