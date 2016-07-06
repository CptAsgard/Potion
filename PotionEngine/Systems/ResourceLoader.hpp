#pragma once

#include <string>
#include <map>
#include <memory>

/**
 * Pag. 320 - Game Engine Architecture,  2nd Edition
 */
namespace Potion
{
	class Resource
	{
	public:
		Resource( uint32_t handle, const std::string& name, const std::string& path ) : handle( handle ), name( name ), path( path ) { }

		const std::string& GetFilename() const { return fileName; }
		const std::string& GetName() const { return name; }
		const std::string& GetPath() const { return path; }
		uint32_t GetHandle() const { return handle; }

	private:
		std::string fileName;
		uint32_t handle;
		std::string name;
		std::string path;

	};

	template <typename T>
	class ResourceLoader
	{
	public:
		/**
		 * Either creates a new resource or returns an already loaded resource
		 */
		void Get( const std::string& name );

	private:
		std::map< std::string, std::unique_ptr<Resource> > resources;

	};

	template<typename T>
	inline void ResourceLoader<T>::Get( const std::string & name )
	{}
}