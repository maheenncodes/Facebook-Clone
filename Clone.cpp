#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

class Date;
class Post;
class User;
class Page;
class Facebook;

#include <iostream>
using namespace std;

class Helper
{
public:
	
	//calculates string of a function
	static int StringLenght(const char* str)
	{
		// This function  returns lenght of str

		int stringLen = 0;
		int i = 0;

		for (i = 0; str[i] != '\0'; i++)
			stringLen++;

		return stringLen;

	}
	//buffers the string
	static char* GetStringFromBuffer(const char* str)
	{
		//this function buffers the string
		int stringLen = StringLenght(str);
		char* bufferedStr = 0;

		if (stringLen > 0)
		{
			bufferedStr = new char[stringLen + 1];

			int i = 0;
			for (; i < stringLen; i++)
				bufferedStr[i] = str[i];

			bufferedStr[i] = '\0';
		}
		return bufferedStr;
	}
	//deallocates the three d array
	static void DeallocateThreeD(char***& temp,int count,int* _array)
	{
		for(int i = 0;i< count ;i++)
		{
			for(int j = 0; j <_array[i];j++)
			{
				delete[] temp[i][j];
			}
			delete[] temp[i];
		}
	    delete[] temp;
	}
	//concatenates two string
	static char* GetStringFromBufferConcatenate(char* str1, char* str2) //This function allocates required memory on heap and copies string in this memory and returns newly created cstring.
	{

		int stringLen1 = StringLenght(str1);
		int stringLen2 = StringLenght(str2);

		char* bufferedStr = 0;

		if (stringLen1 > 0 && stringLen2 > 0)
		{
			int length = stringLen1 + stringLen2 + 2;
			bufferedStr = new char[length];

			int k = 0;
			for (int i = 0; i < stringLen1; i++)
			{
				bufferedStr[k] = str1[i];
				k++;
			}
			bufferedStr[k] = ' ';
			k++;
			for (int i = 0; i < stringLen2; i++)
			{
				bufferedStr[k] = str2[i];
				k++;
			}
			bufferedStr[k] = '\0';
		}

		return bufferedStr;


	}
	//searches a  word from a given word
	static bool SearchWord(char * wordToSearch , char* word)
	{
		int length_1 = StringLenght(wordToSearch);
		int length_2 = StringLenght(word);

		if(length_2 < length_1)
		{
			return false;
		}
		else
		{
			for(int i = 0; i < length_2 ; i++)
			{
				if(word[i] == ' ')
					i++;

				if(word[i] == wordToSearch[0])
				{
					int k = i;
					int j = 0;

					for( j = 0; j < length_1;j++)
					{
						if(word[k]!=wordToSearch[j])
						{
							break;
						}
						k++;
					}
					if(j == length_1)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	//template function for deallocation
	template <class T>
	static void Deallocation(T** array, int length)  //function for deallocation to save memory space
	{
	
		if (array != 0)
		{
			for (int i = 0; i < length; i++)
			{
				delete array[i];
				array[i] = 0;

			}
			delete[] array;
		}
	}
};


//------------------------------------------------------DATE CLASS----------------------------------------------------------------------
class Date
{
private:
	int day;
	int month;
	int year;
public:
	static Date currentDate;
	Date();
	void setDate(int,int,int);
	void CurrentDate(int , int, int);
	void ReadFromFile(ifstream&);
	void Print();
	bool IsLatestPost();
	~Date();


};
Date Date :: currentDate;
Date::Date()
{
}
//reads date from file
void Date::ReadFromFile(ifstream& file)
{
	file >> day >> month >> year ;
}
//sets current date of system
void Date::CurrentDate(int _date , int _month, int _year)
{
	 currentDate.day =_date;
	currentDate.month=_month;
	currentDate.year=_year;

	
}
//prints date
void Date::Print()
{
	cout<<"("<<day<<"/"<<month<<"/"<<year<<")";
}
//checks if the post is latest 
bool Date::IsLatestPost()
{
	if(day == currentDate.day || day == currentDate.day- 1 && month == currentDate.month && year == currentDate.year)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//destructor
Date::~Date()
{ 
}


//-----------------------------------------------------OBJJECT CLASS---------------------------------------------------------------------
class Object
{
protected:
	char* ID;
public:
	
	Object(){ ID = 0;};
	virtual char* GetID(){ return ID;} ;
	virtual void AddPostToTimeline(Post*) {};
	virtual void PrintName() {};
	virtual void PrintNameWithoutID(){};
	virtual ~Object()
	{
		if(ID)
		{
			delete[] ID;
			ID = 0;
		}
	}
};

//--------------------------------------------------------COMMENT CLASS-------------------------------------------------------------------------
class Comment 
{
private:
	char* ID;
	char* text;
	Object* commentBy;
	

public:
	Comment();
	void SetID(char* );
	void SetText(char* );
	void SetCommentBy(Object* );
	void SetComment(char* , char* ,Object* );
	void SetNewComment(char* ,char*,Object* );
	char* GetText();
	void PrintComments();
	~Comment();
};
//constructor
Comment::Comment()
{
	ID = 0;
	text = 0;
    commentBy = 0;
}
//sets id
void Comment::SetID(char* _ID )
{
	ID = _ID;
}
//sets text of comment
void Comment:: SetText(char* _text )
{
	text = _text;
}
//sts the the comment by
void Comment::SetCommentBy(Object* obj )
{
	commentBy = obj;

}
//gets text
char* Comment::GetText()
{
	return text;
}
//prints  comments
void Comment::PrintComments()
{
	commentBy->PrintNameWithoutID();
	cout << " wrote : \"" << text << "\"" << endl;
}
//sets the whole comment
void Comment :: SetComment(char* _id, char* _text,Object* obj)
{
	SetID(_id);
	SetText(_text);
	SetCommentBy(obj);
}
//sets a new comment
void Comment::SetNewComment(char* _ID,char*_text,Object* commenter)
{
	ID = _ID;
	text = _text;
	commentBy = commenter;
}
//destructor
Comment::~Comment()
{
	if(ID)
	{
		delete[] ID;
		ID = 0;
	}
	if(text)
	{
		delete[] text;
		text = 0;
	}
	commentBy = 0;
}
//---------------------------------------------------------POST CLASS-------------------------------------------------------------------------
class Post
{
private:
	char* ID;
	char* text;
	Date sharedDate;
	Object* sharedBy;
	Object** likedBy;
	Comment** comments;
	int noOfComments;
	int noOfLikes;
public:
	Post();
	virtual void LoadPostFromFile(ifstream&);
	void SetSharedBy(Object*);
	void SetLikedBy(Object*, int);
	void SetNoOfLikes(int);
	char* GetPostID();
	Object* GetSharedBy();
	char* GetText();
	Date GetSharedDate();
	void AddComment(Comment*);
	void AddComment(char*,Object*,int);
	void PrintAllComments();
	virtual void PrintFullPost();
	void PrintLatestPost();
	void ViewLikedBy();
	void AddLike(Object* );
	bool SearchPost(char* );
	virtual void PrintPost();
	virtual ~Post();

};
//constructor
Post::Post()
{
	ID = 0;
	text = 0;
	sharedBy = 0;
	likedBy = 0;;
	noOfLikes = 0;
	noOfComments = 0;
	comments= new Comment* [10];
}
//load from file
void Post::LoadPostFromFile(ifstream& file)
{
	char buffer[100];

	file >> buffer;
	ID = Helper::GetStringFromBuffer(buffer);

	sharedDate.ReadFromFile(file);
	file.ignore();

	file.getline(buffer,100,'\n');
	text = Helper::GetStringFromBuffer(buffer);
}
//sets the sharedby
void Post::SetSharedBy(Object* Author)
{
	sharedBy = Author;
}
//getters
Object* Post::GetSharedBy()
{
	return sharedBy;
}
Date Post:: GetSharedDate()
{
	return sharedDate;
}
char* Post::GetText()
{
	return text;
}
void Post::SetLikedBy(Object* liker, int index)
{	
	if(likedBy == NULL)
		return;

	likedBy[index]= liker;
}
//sets the noOfLikes on a post
void Post::SetNoOfLikes(int _likes)
{
	noOfLikes = _likes - 1;

	if(noOfLikes < 0)
		return;
	
	likedBy = new Object* [_likes];
}
//adds comment on a post
void Post::AddComment(Comment* comment)
{
	comments[noOfComments] = comment;
	noOfComments++;
}
//adds new comment on a post
void Post::AddComment(char* _text ,Object* commenter,int noOfComment)
{
	
	comments[noOfComments] = new Comment;
	
	

	int tempID = noOfComment + 1;
	string num = to_string(tempID);
	
	const char *Id = num.c_str();

	char c = 'c';
	

	int length = Helper::StringLenght(Id);

	char* add_ptr = new char[length  + 1];
	for(int i = 0;i< length ;i++)
	{
		add_ptr[i] = Id[i];
	}
	add_ptr[length]='\0';

	
	char* finalId = new char [length + 2];
	finalId[0] = c;

	int j = 0;
	length = length+1;
	for(int i = 1;i< length ;i++)
	{
		finalId[i] = Id[j];
		j++;
	}

	finalId[length] = '\0';

	comments[noOfComments]->SetNewComment(finalId,Helper::GetStringFromBuffer(_text),commenter);
	noOfComments++;

	
}
//prints all comments
void Post::PrintAllComments()
{

	for (int i = 0; i < noOfComments; i++)
	{
		cout<<"        ";
		comments[i]->PrintComments();
	}

}
//prints latest posts
void Post::PrintLatestPost()
{
	if(sharedDate.IsLatestPost() == true)
	{
		sharedBy->PrintNameWithoutID();
		cout<<" shared : "<<text<<"\n";
	}
	PrintAllComments();
}
//prints full post
void Post::PrintFullPost()
{
	cout<<"---";
	sharedBy->PrintNameWithoutID();
	cout<<"shared : "<<text<<"---";

	sharedDate.Print();
	cout<<endl;
	PrintAllComments();
}
//prints post
void Post::PrintPost()
{
	cout<<ID<<" - ";
	GetSharedBy()->PrintNameWithoutID();
	cout << "\"" << GetText() << "\"...    ";
	GetSharedDate().Print();

	cout << endl;
	
	
}
//view thge likes on a post
void Post::ViewLikedBy()
{
	for (int i = 0; i < noOfLikes; i++)
	{
		likedBy[i]->PrintName();
		cout<< endl;
	}
}
//gets post id
char* Post:: GetPostID()
{
	return ID;
}
//adds like on a post
void Post::AddLike(Object* currentUser)
{
	
	likedBy[noOfLikes] = currentUser;
	SetLikedBy(currentUser,noOfLikes);
	noOfLikes++;
}
//seraches the word in the title of the post
bool Post::SearchPost(char* word )
{
	if(Helper::SearchWord(word,text) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//destructor
Post::~Post()
{
	if(ID)
	{
		delete[] ID;
		ID = 0;
	}
	if(text)
	{
		delete[] text;
		text = 0;
	}

	
	if(likedBy)
		delete[] likedBy;

	if(comments)
		delete[] comments;

}
//------------------------------------------------------------------ACTIVITY CLASS-----------------------------------------------------
class Activity : public Post
{
private:
	int typeOfPost;
	char* value;
public:
	Activity();
	void LoadPostFromFile(ifstream& );
	void PrintPost();
	void PrintFullPost();
	~Activity();

};
Activity::Activity()
{
	typeOfPost = 0;
	value = 0;

}
//loads posts activity type from file
void Activity::LoadPostFromFile(ifstream& file)
{
	Post::LoadPostFromFile(file);
	//file.ignore();
	file >> typeOfPost;

	char buffer[100];

	file.ignore();
	file.getline(buffer,100,'\n');
	
	value = Helper::GetStringFromBuffer(buffer);

}
//prints post with comments
void Activity::PrintFullPost()
{
	cout<<"---";
	GetSharedBy()->PrintNameWithoutID();
	if (typeOfPost== 1)
	{
		cout << " is feeling " << value ;
	}
	if (typeOfPost == 2)
	{
		cout << " is thinking about " << value;
	}
	if (typeOfPost == 3)
	{
		cout << " is Making " << value;
	}
	if (typeOfPost == 4)
	{
		cout << " is Celebrating " << value ;
	}
	cout<< "..........";
	GetSharedDate().Print();
	cout<<endl;
	cout << "  \"" ;
	cout<< GetText() << "\"    ";
	
	
	cout << endl;
	PrintAllComments();
	cout<<endl;
	
}
//prints post without comments
void Activity::PrintPost()
{
	cout<<GetPostID()<<" - ";;
	GetSharedBy()->PrintNameWithoutID();
	if (typeOfPost== 1)
	{
		cout << " is feeling " << value ;
	}
	if (typeOfPost == 2)
	{
		cout << " is thinking about " << value;
	}
	if (typeOfPost == 3)
	{
		cout << " is making " << value ;
	}
	if (typeOfPost == 4)
	{
		cout << " is celebrating " << value  ;
	}

	cout<<endl;
	cout << "\"" ;
	cout<< GetText() << "\"...     ";
	GetSharedDate().Print();
	cout << endl;
	
	
	
}
//destructor
Activity::~Activity()
{
	if(value)
	{
		delete[] value;
		value = 0;
	}
}

//--------------------------------------------------------PAGE CLASS-------------------------------------------------------------------
class Page  : public Object 
{
private:

	
	char* Title;   //name of the page
	Post** timeLine;
	int noOfPosts;

public:
	Page();  //constructor
	void LoadDataFromFile(ifstream&, int&);  //to load data from page file
	char* GetPageID();   //returns page id
	void PrintName();
	void PrintNameWithoutID();
	void AddPostToTimeline(Post* );
	void PrintLatestPosts();
	void PrintAllPostsOfPage();
	bool SearchPage(char* );
	~Page(); //destructor

};
//constructor
Page::Page()
{
	ID = 0;
	Title = 0;
	noOfPosts = 0;
	timeLine = new Post* [10];
}
//to load data from page file
void Page::LoadDataFromFile(ifstream& file, int& noOfPage)
{
	char buffer[80];


	file >> buffer;
	file.ignore();
	ID = Helper::GetStringFromBuffer(buffer);

	file.getline(buffer, 50, '\n');
	Title = Helper::GetStringFromBuffer(buffer);




}  
//returns page id for search function 
char* Page::GetPageID()
{
	return ID;
}
//print id and title of page
void Page::PrintName()
{
	cout<<ID<<" "<<Title;
}
void Page::PrintNameWithoutID()
{
	cout<<Title;
}
//adds the post associated with page to its timeline
void Page::AddPostToTimeline(Post* post)
{
	timeLine[noOfPosts]  = post;
	noOfPosts++;
}
//prints lastest posts of pages timeline
void Page::PrintLatestPosts()
{
	for (int i = 0; i < noOfPosts; i++)
	{
        timeLine[i]->PrintLatestPost();
	}
}
//prints all post of timeline of page
void Page::PrintAllPostsOfPage()
{
	for(int i = 0; i< noOfPosts;i++)
	{
		
		timeLine[i]->PrintFullPost();
	}
}
//searches a word in the title of the page
bool Page::SearchPage(char* word )
{
	if(Helper::SearchWord(word,Title ) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//destructor
Page::~Page()
{
	if (Title != 0)
	{
		delete[]Title;
		Title = 0;
	}

	if(timeLine)   //deleting liked by objects list
		Helper::Deallocation(timeLine, noOfPosts);
}

//------------------------------------------------------------------------USER CLASS----------------------------------------------------
class User : public Object
{
private:
	
	char* FirstName;   
	char* LastName;
	int friendCount;  //count of users friend
	int pagesCount;    //count of users liked pages
	int noOfPosts;
	int* pageCountArray;
	int* friendCountArray;
	User** FriendList;  //has info of users friends
	Page** LikedPages;   //has info of users liked pages
	Post** timeLine;
	
public:


	User(); //default conatructor
	void GetUserDataFromFile(ifstream&, int&, char**&, char**&);  //to load data from users file
	char* GetUserID();          //for search function
	char* GetUserFirstName();  //for currentUser function
	char* GetUserLastName();
	int GetFriendCount();
	int GetPagesCount();
	void SetFriendListRow(int);
	void SetFriendListCol(int,User*);
	void SetPageListRow(int);
	void SetPageListCol(int,Page*);
	void PrintName();   //prints id and name of user
	void PrintNameWithoutID(); //Prints only name of the user
	void ViewFriendList();   //displays users friends
	void ViewLikedPages();    //displays users liked pages
	void AddPostToTimeline(Post* post);
	void PrintLatestPostByFriend();
	void ViewHome();
	void ViewTimeLine();
	bool SearchUser(char*);
	~User();    //destructor
	


};
//constructor
User::User()
{
	
	FirstName = 0;
	LastName = 0;
	friendCount = 0;
	pagesCount = 0;
	FriendList = 0;
	LikedPages = 0;
	timeLine = new Post*[10];
	noOfPosts  = 0;
}
//loads data from users file
void User::GetUserDataFromFile(ifstream& file, int& noOfUser, char** &tempFriendList, char** &tempPageList)
{
	
	char buffer[50];

	file>>buffer;
	ID = Helper::GetStringFromBuffer(buffer);

	file >> buffer;
	FirstName = Helper::GetStringFromBuffer(buffer);

	file >> buffer;
	LastName = Helper::GetStringFromBuffer(buffer);

	char** FriendsList = new char* [11];
		
	int length = 0;

	while (buffer[0] != '-')   //calculates no of friends
	{
		file >> buffer;
			
		if (buffer[0] != '-')
		{
			FriendsList[length] = Helper::GetStringFromBuffer(buffer);
				
			length++;
		}
			
	}
	FriendsList[length] = '\0';
	friendCount = length;

	tempFriendList = new char* [length + 1 ];

	int j = 0;
	for ( j = 0; j < length; j++)
	{
		tempFriendList[j] = FriendsList[j];  //copies the ids of friends in a temp array
	}
	tempFriendList[j] = 0;

	
		

	char** PagesList = new char* [11];
		
	length = 0;

	buffer[0] = 'A';  //as previous buffer is - so changing the value to enter while loop

	while (buffer[0] != '-')
	{
			
		file >> buffer;
		if (buffer[0] != '-')        //calculates no of pages
		{
			PagesList[length] = Helper::GetStringFromBuffer(buffer);
			length++;
		}
			
	}
	PagesList[length] = '\0';
	pagesCount = length;
	
		
	tempPageList = new char* [length + 1];

		j = 0;
	for (j = 0; j < length; j++)
	{
		tempPageList[j] = PagesList[j];   //copies the ids of pages
	}
	tempPageList[j] = 0;

	

}
//getters
char* User::GetUserID()
{
	return ID;
}
char* User :: GetUserFirstName()
{
	return FirstName;
}
char* User::GetUserLastName()
{
	return LastName;
}
int User::GetFriendCount()
{
	return friendCount;
}
int User::GetPagesCount()
{
	return pagesCount;
}
//prints name with id
void User:: PrintName()
{
	cout << ID << " " << FirstName << " " << LastName ;
}
//prints name without id
void User::PrintNameWithoutID()
{
	cout << FirstName << " " << LastName ;
}
//allocates seize of FriendList
void User::SetFriendListRow(int count)
{
	FriendList = new User*[count ];
}
// allocates columns of friendlist
void User::SetFriendListCol(int index, User* _user)
{
	
	FriendList[index] = _user;
}
//allocates seize of pageList
void User::SetPageListRow(int count)
{
	LikedPages = new Page*[count ];
}
// allocates columns of pagelist
void User::SetPageListCol(int index, Page* page)
{
	//LikedPages[index] = new Page;
	LikedPages[index] = page;
}
//displays friends list
void User::ViewFriendList()
{
	
	for (int i = 0; i < friendCount; i++)
	{
		FriendList[i]->PrintName();
		cout<<endl;
	}

}
//displays likes pages list
void User::ViewLikedPages()
{
	
	for (int i = 0; i < pagesCount; i++)
	{
		LikedPages[i]->PrintName();
		cout<<endl;
	}
}
//adds post to users timeline
void User::AddPostToTimeline(Post* post)
{
	timeLine[noOfPosts]  = post;
	noOfPosts++;
}
//prints latest post by friend
void User::PrintLatestPostByFriend()
{
	for (int i = 0; i < noOfPosts; i++)
	{
		timeLine[i]->PrintLatestPost();
	}
}
//views home of user
void User::ViewHome()
{
	for (int i = 0; i<GetFriendCount(); i++)
	{
		FriendList[i]->PrintLatestPostByFriend();
		cout << endl << endl;
	}

	for (int i = 0; i<pagesCount; i++)
	{
		LikedPages[i]->PrintLatestPosts();
		cout << endl << endl;
	
	}
}
//shows the timeLine of user
void User::ViewTimeLine()
{
	for (int i = 0; i < noOfPosts; i++)
		timeLine[i]->PrintFullPost();
}
//searches a word in users name
bool User::SearchUser(char* word )
{
	if(Helper::SearchWord(word,Helper::GetStringFromBufferConcatenate(FirstName,LastName ) )== true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//destructor
User::~User()
{
	
	if (FirstName != 0)
	{
		delete[]FirstName;
		FirstName = 0;
	}
	if (LastName != 0)
	{
		delete[]LastName;
		LastName = 0;
	}
	delete[] FriendList;
	delete[] LikedPages;

	if(timeLine)
		Helper::Deallocation(timeLine, noOfPosts);
}
//social network class
class Facebook
{
private:
	
	User** UsersList;
	Page** PageList;
	Post** PostList;
	User* CurrentUser;
	Date* systemDate;
	int totalUsers;
	int totalPages;
	int totalPosts;
	int totalComments;
	int* friendCountArray;
	int* pageCountArray;

	// functions to search user page and post repectively
	Page* SearchPageByID( const char* page)
	{
		for (int i = 0; i < totalPages; i++)
		{
			if (strcmp(page,PageList[i]->GetPageID())==0)
			{
				return PageList[i];
			}
		}
		return 0;
	}  
	User* SearchUserByID( const char* user)
	{
		for (int i = 0; i < totalUsers; i++)
		{
			if (strcmp(user,UsersList[i]->GetUserID())== 0)
			{
				return UsersList[i];
			}
		}
		return 0;
	}
	Post* SearchPostByID( const char* post)
	{
		for (int i = 0; i < totalPages; i++)
		{
			if (strcmp(post,PostList[i]->GetPostID())==0)
			{
				return PostList[i];
			}
		}
		return 0;
	}
public:

	User* SetCurrentUser( const char*);  //sets the current user
	Facebook();
	void LoadData(char***& ,char***&);
	void LoadPosts();
	void LoadComments();
	void AssociateFriends(char***);   //associates the users in the friend list of user
	void AssociatePages(char***);      //associates the pages in the friend list of pages
	void ViewLikesList(char*);
	void LikePost(char* );
	void AddComment(char* ,char*);
	void ShowPost(char*);
	void ViewPage(char*);
	void Search(char*);
	void Run();  //to run the social networking class
	~Facebook();  //destructor
	
	
};
Facebook::Facebook()
{
	CurrentUser = 0;

	UsersList = 0;
	PageList = 0;
	PostList = 0;

}
//loads data from both pages and users file
void Facebook::LoadData(char*** &tempFriendsList ,char*** &PagesLiked)
{
	ifstream UsersFile("Users.txt");

	if (UsersFile)
	{
		UsersFile >> totalUsers;

		UsersList = new User* [totalUsers];
		

		tempFriendsList = new char** [totalUsers + 1];
		tempFriendsList[totalUsers] = 0;

		PagesLiked = new char** [totalUsers + 1];
		PagesLiked[totalUsers] = 0;

		for (int i = 0; i < totalUsers; i++)
			UsersList[i] = new User;
		
		for (int  i= 0; i < totalUsers; i++)
			UsersList[i]->GetUserDataFromFile(UsersFile, i,tempFriendsList[i],PagesLiked[i]);   //gets users data
		
	}
	UsersFile.close();


	ifstream PageFile("Pages.txt");

	if (PageFile)
	{
		PageFile >> totalPages;

		PageList = new Page* [totalPages];


		for (int i = 0; i < totalPages; i++)
			PageList[i] = new Page;

		int i = 0;
		PageFile.ignore();
		for (i = 0; i < totalPages; i++)
		{
			PageList[i]->LoadDataFromFile(PageFile, i);  //gets page data from file
		}


	}
	PageFile.close();

}
//loads post from file
void Facebook:: LoadPosts()
{
	ifstream file ("Posts.txt");

	if(file)
	{
		char buffer[100];
		file>>totalPosts;

		PostList = new Post* [totalPosts];


		int i = 0;
		for ( i = 0; i < totalPosts; i++)
		{
			int type;
			file>> type;

			if(type ==1)
			{
				PostList[i] = new Post;
			}
			else
			{
				PostList[i] = new Activity;
			}
			PostList[i]->LoadPostFromFile(file);  //gets post data from file

			Object* sharedBy;

			file>>buffer;

			if(buffer[0] =='u')
			{
				sharedBy = SearchUserByID(buffer);
			}
			else
			{
				sharedBy = SearchPageByID(buffer);
			}
			PostList[i]->SetSharedBy(sharedBy);
			sharedBy->AddPostToTimeline(PostList[i]);
		   
		   char templikedBy[20][3];
		   int likes = 0;

		 
			while (buffer[0] != '-')   //calculates no of likes
			{
				file >> buffer;
			
				if (buffer[0] != '-')
				{
					
				    templikedBy[likes][0] = buffer[0];
					templikedBy[likes][1] = buffer[1];
					templikedBy[likes][2] = '\0';
					likes++;
				}
			
			}
			
			Object** likedBy = new Object* [likes];
			PostList[i]->SetNoOfLikes(likes);
			for(int j = 0; j < likes;j++)
			{
				if(templikedBy[j][0] == 'u')
				{
					likedBy[j] = SearchUserByID(templikedBy[j]);
				}
				else
				{
					likedBy[j] = SearchPageByID(templikedBy[j]);
				}
				PostList[i]->SetLikedBy(likedBy[j],j);
				
			}
			
		
		}
		
	}
}
//loads comments from comment file
void Facebook:: LoadComments()
{
	
	ifstream file("Comments.txt"); 
	
	char* Id;
	char* postID;
	char* sharedBy;
	char* text;

	char buffer[100];
	if(file)
	{   
		file>>totalComments;

		Comment** tempcoment = new Comment*[totalComments];

		for(int i=0;i<totalComments;i++)
		{
			
			file>>buffer;
			Id=Helper::GetStringFromBuffer(buffer);
			
			file>>buffer;
			postID=Helper::GetStringFromBuffer(buffer);	

			file>>buffer;
			sharedBy=Helper::GetStringFromBuffer(buffer);
			file.ignore();

			file.getline(buffer,100,'\n');
			text=Helper::GetStringFromBuffer(buffer);

			tempcoment[i] = new Comment;
			Object* Sharedby;

			if(sharedBy[0] =='u')
			{
				
				Sharedby = SearchUserByID(sharedBy);
				
			}
			else
			{
				Sharedby = SearchPageByID(sharedBy);
			}

			tempcoment[i]->SetComment(Id,text,Sharedby); //sets the comment
			
			Post* PostofComment=SearchPostByID(postID);
			PostofComment->AddComment(tempcoment[i]);

		}
		delete [] tempcoment;
	}
}
//associates the users in the friend list of user
void Facebook::AssociateFriends(char*** temp)
{
	friendCountArray = new int [totalUsers];

	for (int i = 0; i < totalUsers; i++)
	{
		
		friendCountArray[i] = UsersList[i]->GetFriendCount(); 


		UsersList[i]->SetFriendListRow(friendCountArray[i]);

		int j = 0;
		for (j = 0; j < friendCountArray[i]; j++)
		{
			UsersList[i]->SetFriendListCol(j,SearchUserByID(temp[i][j]));
		}
		
		
	}
}
//associates the pages in the friend list of pages
void Facebook::AssociatePages(char*** temp)
{
	pageCountArray = new int[totalUsers];
	for (int i = 0; i < totalUsers; i++)
	{
		pageCountArray[i] = UsersList[i]->GetPagesCount();

		UsersList[i]->SetPageListRow(pageCountArray[i]);
		
		int j = 0;
		for (j = 0; j < pageCountArray[i]; j++)
		{
			UsersList[i]->SetPageListCol(j, SearchPageByID(temp[i][j]));
		}
		
	}


}
//sets current user
User* Facebook::SetCurrentUser( const char* user)
{

	CurrentUser = SearchUserByID(user);
	CurrentUser->PrintNameWithoutID();
	cout << " sucessfully set as Current User\n";
	return CurrentUser;
	
}
//Views the likes of a post
void Facebook::ViewLikesList(char* temp )
{
	Post * post =SearchPostByID(temp);
	cout<<"Post Liked By:\n";
	post->ViewLikedBy();
}
//Adds a like to a post
void Facebook :: LikePost(char* temp)
{
	Post* post = SearchPostByID(temp);
	post->AddLike(CurrentUser);
	cout<<"Post Liked Sucessfully!\n";
}
//adds a comment to a post
void Facebook::AddComment(char* temp, char* tempText)
{
	temp = Helper::GetStringFromBuffer(temp);
	tempText = Helper::GetStringFromBuffer(tempText);
	Post* post = SearchPostByID(temp);
	post->AddComment(tempText,CurrentUser,totalComments);
	cout<<"Comment Added Sucessfully!\n";
}
//shows a post
void Facebook:: ShowPost(char* tempID)
{
	Post* post = SearchPostByID(tempID);

	post->PrintFullPost();
}
//views the whole page with posts
void Facebook::ViewPage(char* temp)
{
	Page* page = SearchPageByID(temp);
	page->PrintAllPostsOfPage();
}
//searches a specific keyword
void Facebook::Search(char* word)
{
	cout<<endl;
	cout<<"Users:"<<endl;

	for(int i = 0; i< totalUsers ; i++)
	{
		if(UsersList[i]->SearchUser(word) == true) //calls the ssearch function of user
		{
			cout<<"-";
			UsersList[i]->PrintNameWithoutID();
			cout<<endl;
		}
	}

	


	cout<<endl;
	cout<<"Posts:"<<endl;

	for(int i = 0; i < totalPosts ; i++)
	{
		if(PostList[i]->SearchPost(word) == true)
		{
			cout<<"----";
			PostList[i]->PrintPost();
			cout<<endl;
		}
	}
	


	cout<<endl;
	cout<<"Pages:"<<endl;

	for(int i = 0; i < totalPages ; i++)
	{
		if(PageList[i]->SearchPage(word) == true)
		{
			
			PageList[i]->PrintName();
			cout<<endl;
		}
	}
	
}
//destructor
Facebook::~Facebook()
{
	Helper::Deallocation(UsersList, totalUsers);

	Helper::Deallocation(PageList,totalPages);

	if(PostList)
		delete[] PostList;

	
	CurrentUser = 0;
}
//runs the facebook
void Facebook::Run()
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                                SOCIAL NETWORKING PROJECT                                                  " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	char*** tempFriendList = 0;
	char*** tempLikedPages = 0;
	
	LoadData(tempFriendList, tempLikedPages);
    LoadPosts();
	LoadComments();

	
	AssociateFriends(tempFriendList);
	AssociatePages(tempLikedPages);

	cout << "\nCOMMAND:\t\t\t\tSET USER u7" << endl;
	User* CurrentUser = SetCurrentUser("u7");

	Date::currentDate.CurrentDate(15,11,2017);
	cout << "\nCOMANND:\t\t\tSET SYSTEM DATE 15 11 2017" << endl;
	cout<<"System Date:      ";
	Date::currentDate.Print();
	cout<< endl;
	
	cout<<endl;

	
	cout << "\nCOMMAND:\t\t\t\tVIEW FRIEND LIST" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	CurrentUser->PrintNameWithoutID();
	cout<<"---Friend List\n\n\n";
	CurrentUser->ViewFriendList();

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW LIKED  PAGES" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	CurrentUser->PrintNameWithoutID();
	cout << "---Liked Pages\n\n\n";
	CurrentUser->ViewLikedPages();
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW HOME" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	CurrentUser->PrintNameWithoutID() ;
	cout  << "---Home\n\n\n";
	CurrentUser->ViewHome();

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW TIMELINE" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	CurrentUser->PrintNameWithoutID() ;
	cout  << "---TimeLine\n\n\n";
	CurrentUser->ViewTimeLine();

		
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW LIKED LIST(post5)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	ViewLikesList("post5");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tLIKE POST(post5)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	LikePost("post5");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW LIKED LIST(post5)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	ViewLikesList("post5");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tPOST COMMENT(post4, Good Luck for your Result)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	AddComment("post4", "Good Luck for your Result");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW POST(post4)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	ShowPost("post4");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tPOST COMMENT(post8, Thanks for the wishes)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	AddComment("post8", "Thanks for the wishes");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW POST(post8)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	ShowPost("post8");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tVIEW PAGE(p1)" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	ViewPage("p1");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tSEARCH Birthday " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	Search("Birthday");

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\nCOMMAND:\t\t\t\tSEARCH Ali " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	Search("Ali");


	Helper::DeallocateThreeD(tempFriendList,totalUsers,friendCountArray);  //deallocation of three d arrays to save memory space
	Helper::DeallocateThreeD(tempLikedPages,totalPages,pageCountArray);

}
void main()
{
	system("color 1f");
	{
	Facebook fb;
	fb.Run();
	}
	system ("pause");
}