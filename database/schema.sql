PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS users (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	username TEXT NOT NULL UNIQUE,
	full_name TEXT NOT NULL,
	email TEXT NOT NULL UNIQUE,
	password_hash TEXT NOT NULL,
	bio TEXT DEFAULT '',
	created_at TEXT NOT NULL,
	updated_at TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS communities (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	owner_id INTEGER NOT NULL,
	name TEXT NOT NULL UNIQUE,
	description TEXT NOT NULL,
	created_at TEXT NOT NULL,
	updated_at TEXT NOT NULL,
	FOREIGN KEY (owner_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS community_members (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	community_id INTEGER NOT NULL,
	user_id INTEGER NOT NULL,
	role_in_community TEXT NOT NULL DEFAULT 'member',
	joined_at TEXT NOT NULL,
	UNIQUE(community_id, user_id),
	FOREIGN KEY (community_id) REFERENCES communities(id) ON DELETE CASCADE,
	FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS auth_tokens (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	user_id INTEGER NOT NULL,
	token TEXT NOT NULL UNIQUE,
	expires_at TEXT NOT NULL,
	revoked_at TEXT,
	created_at TEXT NOT NULL,
	FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS posts (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	user_id INTEGER NOT NULL,
	community_id INTEGER NOT NULL,
	title TEXT NOT NULL,
	body TEXT NOT NULL,
	created_at TEXT NOT NULL,
	updated_at TEXT NOT NULL,
	FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
	FOREIGN KEY (community_id) REFERENCES communities(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS comments (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	post_id INTEGER NOT NULL,
	user_id INTEGER NOT NULL,
	body TEXT NOT NULL,
	created_at TEXT NOT NULL,
	updated_at TEXT NOT NULL,
	FOREIGN KEY (post_id) REFERENCES posts(id) ON DELETE CASCADE,
	FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS likes (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	user_id INTEGER NOT NULL,
	content_kind TEXT NOT NULL CHECK (content_kind IN ('post', 'comment')),
	content_id INTEGER NOT NULL,
	created_at TEXT NOT NULL,
	UNIQUE(user_id, content_kind, content_id),
	FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS follows (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	follower_id INTEGER NOT NULL,
	following_id INTEGER NOT NULL,
	created_at TEXT NOT NULL,
	UNIQUE(follower_id, following_id),
	CHECK (follower_id <> following_id),
	FOREIGN KEY (follower_id) REFERENCES users(id) ON DELETE CASCADE,
	FOREIGN KEY (following_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS password_reset_tokens (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	user_id INTEGER NOT NULL,
	token TEXT NOT NULL UNIQUE,
	expires_at TEXT NOT NULL,
	used_at TEXT,
	created_at TEXT NOT NULL,
	FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_auth_tokens_user_id ON auth_tokens(user_id);
CREATE INDEX IF NOT EXISTS idx_auth_tokens_token ON auth_tokens(token);

CREATE INDEX IF NOT EXISTS idx_posts_user_id ON posts(user_id);
CREATE INDEX IF NOT EXISTS idx_posts_community_id ON posts(community_id);

CREATE INDEX IF NOT EXISTS idx_comments_post_id ON comments(post_id);
CREATE INDEX IF NOT EXISTS idx_comments_user_id ON comments(user_id);

CREATE INDEX IF NOT EXISTS idx_likes_user_id ON likes(user_id);
CREATE INDEX IF NOT EXISTS idx_likes_content_kind_id ON likes(content_kind, content_id);

CREATE INDEX IF NOT EXISTS idx_follows_follower_id ON follows(follower_id);
CREATE INDEX IF NOT EXISTS idx_follows_following_id ON follows(following_id);

CREATE INDEX IF NOT EXISTS idx_communities_owner_id ON communities(owner_id);

CREATE INDEX IF NOT EXISTS idx_community_members_community_id ON community_members(community_id);
CREATE INDEX IF NOT EXISTS idx_community_members_user_id ON community_members(user_id);

CREATE INDEX IF NOT EXISTS idx_password_reset_tokens_user_id
ON password_reset_tokens(user_id);

CREATE INDEX IF NOT EXISTS idx_password_reset_tokens_token
ON password_reset_tokens(token);
