defmodule Eigen.Matrix3d do
  @moduledoc false

  defstruct ~w{
    __reference__
  }a

  @on_load :load_nifs

  @doc false
  @spec load_nifs :: :ok
  def load_nifs do
    priv_dir =
      case :code.priv_dir(__MODULE__) do
        {:error, _error} ->
          :code.which(__MODULE__)
          |> :filename.dirname()
          |> :filename.dirname()
          |> Path.join("priv")

        path ->
          path
      end

    case :erlang.load_nif(Path.expand(:filename.join(priv_dir, "matrix3d")), 0) do
      :ok ->
        :ok

      {:error, {:load_failed, reason}} ->
        IO.warn("Error loading NIF #{reason}")
        :ok
    end
  end

  def matrix3d_empty(), do: :erlang.nif_error(:nif_library_not_loaded)
  def matrix3d_new(_list), do: :erlang.nif_error(:nif_library_not_loaded)
  def matrix3d_to_list(ref) when is_reference(ref), do: :erlang.nif_error(:nif_library_not_loaded)

  def new() do
    reference = matrix3d_empty()
    %__MODULE__{__reference__: reference}
  end

  def new([first | _] = list) when is_list(first) do
    reference = matrix3d_new(list)
    %__MODULE__{__reference__: reference}
  end

  def to_list(%__MODULE__{} = matrix) do
    matrix3d_to_list(matrix.__reference__)
  end
end
