defmodule Eigen.MixProject do
  use Mix.Project

  @github_link "https://github.com/sparta-science/eigen"
  @version "0.1.0"

  def project do
    [
      app: :eigen,
      compilers: [:elixir_make | Mix.compilers()],
      deps: deps(),
      description: description(),
      elixir: "~> 1.6",
      make_clean: ["clean"],
      make_error_message: make_error_message(),
      make_executable: make_executable(),
      make_makefile: "src/Makefile",
      make_targets: ["all"],
      name: "Eigen",
      package: package(),
      source_url: @github_link,
      start_permanent: Mix.env() == :prod,
      version: @version
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      {:elixir_make, "~> 0.5", runtime: false},
      {:ex_doc, ">= 0.0.0", only: :dev, runtime: false}
    ]
  end

  defp description do
    "Use the Eigen C++ libraries in Elixir"
  end

  defp make_executable do
    case :os.type() do
      {:win32, _} ->
        "mingw32-make"

      _ ->
        :default
    end
  end

  defp package do
    [
      files: [
        "lib",
        "src",
        "README.md",
        "mix.exs"
      ],
      maintainers: [
        "Sparta Science"
      ],
      licenses: ["simplified BSD"],
      build_tools: ["make"],
      links: %{
        "GitHub" => @github_link
      }
    ]
  end

  defp make_error_message do
    case :os.type() do
      {:win32, _} -> "Unable to compile on Windows."
      _ -> :default
    end
  end
end
