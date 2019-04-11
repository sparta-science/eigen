defmodule Eigen.NIFs do
  @moduledoc false

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

    case :erlang.load_nif(Path.expand(:filename.join(priv_dir, "eigen")), 0) do
      :ok ->
        :ok

      {:error, {:load_failed, reason}} ->
        IO.warn("Error loading NIF #{reason}")
        :ok
    end
  end

  def hello(), do: :erlang.nif_error(:nif_library_not_loaded)
end
