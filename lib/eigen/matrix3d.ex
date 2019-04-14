defmodule Eigen.Matrix3d do
  @moduledoc false

  alias Eigen.Nif

  defstruct ~w{
    __reference__
  }a

  def new() do
    {:ok, reference} = Nif.matrix3d_empty()
    %__MODULE__{__reference__: reference}
  end

  def new([first | _] = list) when is_list(first) do
    {:ok, reference} = Nif.matrix3d_new(list)
    %__MODULE__{__reference__: reference}
  end

  def div(%__MODULE__{} = matrix, divisor) do
    with {:ok, reference} <- Nif.matrix3d_div_scalar(matrix.__reference__, divisor) do
      {:ok, %__MODULE__{__reference__: reference}}
    else
      {:error, message} -> {:error, to_string(message)}
    end
  end

  def mult(%__MODULE__{} = matrix, multiplier) do
    with {:ok, reference} <- Nif.matrix3d_mult_scalar(matrix.__reference__, multiplier) do
      {:ok, %__MODULE__{__reference__: reference}}
    else
      {:error, message} -> {:error, to_string(message)}
    end
  end

  def to_list(%__MODULE__{} = matrix) do
    with {:ok, list} <- Nif.matrix3d_to_list(matrix.__reference__) do
      list
    else
      {:error, message} -> {:error, to_string(message)}
    end
  end
end
